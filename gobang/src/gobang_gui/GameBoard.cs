using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace gobang_gui
{

    // a game piece
    class GamePiece
    {
        public Color Color { set; get; }
        public bool IsOk { set; get; }
        public int Step { set; get; }
    }

    // a game board
    class GameBoard : Control
    {
        private TextBox _txtGameLog;
        private GamePieceActionHandler _moveHandler;

        public GameBoard(TextBox txtGameLog, GamePieceActionHandler moveHandler)
        {
            this.BackColor = Color.FromArgb(243, 243, 243);
            this.Dock = DockStyle.Fill;
            this.PaintLine = Color.FromArgb(110, 110, 110);

            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.DoubleBuffer, true);

            this.MouseClick += new MouseEventHandler(Gobang_MouseClick);

            this._txtGameLog = txtGameLog;
            this._moveHandler = moveHandler;

            InitMatrix();
        }

        // square of radius value
        private float _RadiusSquare = 0;
        // a step recorder, odd = black, not odd = white
        private int _Step = 0;
        public int Step
        {
            get { return _Step; }
        }

        // vertical lines count
        private int _vertical = 20;
        public int Vertical
        {
            get { return _vertical; }
            set
            {
                _vertical = value;
                InitMatrix();
                Invalidate();
            }
        }

        // horizontal lines count
        private int _horizontal = 20;
        public int Horizontal
        {
            get { return _horizontal; }
            set
            {
                _horizontal = value;
                InitMatrix();
                Invalidate();
            }
        }

        // line colour
        private Color _paintLine = Color.Black;
        public Color PaintLine
        {
            get { return _paintLine; }
            set { _paintLine = value; }
        }

        // while the system is requiring me to paint the game board
        protected override void OnPaint(PaintEventArgs pe)
        {
            float vag_width = (float)(1.0 * this.Width / this._vertical);
            float vag_height = (float)(1.0 * this.Height / this._horizontal);

            this._RadiusSquare = (vag_width * vag_width + vag_height * vag_height) / 9;

            pe.Graphics.SmoothingMode = SmoothingMode.HighQuality;

            using (Pen pen = new Pen(new SolidBrush(_paintLine), 2))
            {
                pen.StartCap = LineCap.Round;
                pen.EndCap = LineCap.Round;
                for (int row = 1; row <= this._horizontal; row++)
                {
                    pe.Graphics.DrawLine(pen, (float)(vag_width * 0.5), (float)(vag_height * (row - 0.5)), (float)(vag_width * (this._vertical - 0.5)), (float)(vag_height * (row - 0.5)));
                    base.OnPaint(pe);
                }

                for (int col = 1; col <= this._vertical; col++)
                {
                    pe.Graphics.DrawLine(pen, (float)(vag_width * (col - 0.5)), (float)(vag_height * 0.5), (float)(vag_width * (col - 0.5)), (float)(vag_height * (this._horizontal - 0.5)));
                    base.OnPaint(pe);
                }
            }


            for (int row = 0; row < this._horizontal; row++)
            {
                for (int col = 0; col < this._vertical; col++)
                {
                    GamePiece piec = _Matrix[row * this._vertical + col];
                    // draw all GamePieces at their current states
                    if (piec.IsOk)
                    {
                        using (SolidBrush solidBrush = new SolidBrush(
                            piec.Step % 2 == 1 ? 
                            Color.FromArgb(51, 51, 51) :    // odd, draw black
                            Color.White))                   // not odd, draw white
                        {
                            float x = (float)((col + 0.18) * vag_width);
                            float y = (float)((row + 0.18) * vag_height);
                            float width = (float)(vag_width * 0.65);
                            float height = (float)(vag_height * 0.65);

                            pe.Graphics.FillEllipse(solidBrush, x, y, width, height);
                            base.OnPaint(pe);
                        }
                    }
                }
            }
        }

        // a matrix of game pieces which records all game pieces's states and tell whether they shall be drawn at paint time or not
        private GamePiece[] _Matrix;

        // initialise a new matrix, which has 19*19 not-activated GamePieces
        private void InitMatrix()
        {
            _Matrix = new GamePiece[this._horizontal * this._vertical];

            for (int i = 0; i < _Matrix.Length; i++)
            {
                _Matrix[i] = new GamePiece
                {
                    IsOk = false,
                    Step = 0
                };
            }
        }

        // internal method of a piece moving
        private void moveTo(int x, int y)
        {
            GamePiece piec = this._Matrix[x + y * this._vertical];
            if (!piec.IsOk)
            {
                piec.Step = ++_Step;

                if (piec.Step % 2 == 1)
                {
                    this._moveHandler.BlackMove(x, y);
                }
                else
                {
                    this._moveHandler.WhiteMove(x, y);

                }

                // activate the piece
                piec.IsOk = true;
                Invalidate();
            }
        }

        // when the mouse was pressed, the GamePiece shall be drown
        private void Gobang_MouseClick(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    // only when the left mouse button was pressed shall a GamePiece be drown
                    float vag_width = (float)(1.0 * this.Width / this._vertical);
                    float vag_height = (float)(1.0 * this.Height / this._horizontal);

                    // find the nearest pressing point on the game board
                    int nx = (int)Math.Round(e.X / vag_width - 0.5);
                    int ny = (int)Math.Round(e.Y / vag_height - 0.5);

                    float div_width = (float)((nx + 0.5) * vag_width) - e.X;
                    float div_height = (float)((ny + 0.5) * vag_height) - e.Y;

                    if (div_width * div_width + div_height * div_height <= this._RadiusSquare)
                    {
                        moveTo(nx, ny);
                    }

                    break;
                //case MouseButtons.Right:
                //    //点击右键，表示撤销步骤
                //    int maxpos = 0;
                //    for (int i = 0; i < _Matrix.Length; i++)
                //    {
                //        if (_Matrix[i].IsOk && _Matrix[i].Step == _Step)
                //        {
                //            _Step--;
                //            _Matrix[i].Step = 0;
                //            _Matrix[i].IsOk = false;

                //            Invalidate();

                //            break;
                //        }
                //    }

                //    break;
            }
        }


        // lock the whole block
        public void Lock()
        {
            this.Enabled = false;
        }

        // unlock the whole block
        public void UnLock()
        {
            this.Enabled = true;
        }

        // move the current game piece to some place
        public void MovePiece(int x, int y)
        {
            moveTo(x, y);
        }

    }

    // things to do after a move was conducted
    public interface GamePieceActionHandler
    {
        bool BlackMove(int x, int y);
        bool WhiteMove(int x, int y);
    }

}

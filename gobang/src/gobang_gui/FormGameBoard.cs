using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DarkUI.Forms;

namespace gobang_gui
{

    public delegate bool MoveHandlerDelegate(int x, int y);

    public class MoveHandler : GamePieceActionHandler
    {

        private MoveHandlerDelegate _blackHandler;
        private MoveHandlerDelegate _whiteHandler;

        public MoveHandler(MoveHandlerDelegate black, MoveHandlerDelegate white)
        {
            this._blackHandler = black;
            this._whiteHandler = white;
        }

        public bool BlackMove(int x, int y)
        {
            return _blackHandler(x, y);
        }

        public bool WhiteMove(int x, int y)
        {
            return _whiteHandler(x, y);
        }
    }

    public partial class FormGameBoard : Form
    {
        private GameBoard gameBoard;

        public FormGameBoard()
        {
            InitializeComponent();

            this.gameBoard = new GameBoard(this.txtGameLog, 
                new MoveHandler(
                    (x, y) => {
                        // TODO
                        this.txtGameLog.AppendText(gameBoard.Step + "> Black moved at (" + x + ", " + y + ");\n");
                        return true;
                    },
                    (x, y) => {
                        // TODO
                        this.txtGameLog.AppendText(gameBoard.Step + "> White moved at (" + x + ", " + y + ");\n");
                        return true;
                    }
                )
            );
            gameBoard.MovePiece(9, 9);
            this.gameBoardPanel.Controls.Add(this.gameBoard);
        }

        private void mnuFile_Click(object sender, EventArgs e)
        {

        }

        private void aIChallengeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void aboutGobangToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void playersToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void exitGobangToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        // clicked the game board
        private void gameBoardBox_MouseClick(object sender, MouseEventArgs e)
        {
            
        }

        private void darkSectionPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void FormGameBoard_Load(object sender, EventArgs e)
        {

        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DarkUI.Forms;
using gobang_gui.controllers;
using System.Threading;

namespace gobang_gui.forms
{
    public partial class FormGameBoard : Form
    {
        public enum GameClass
        {
            WITH_AI, WITH_HUMAN
        }

        private GameBoard _gameBoard;
        private GameClass _gameClass;
        private System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();

        public FormGameBoard(GameClass gameClass)
        {
            InitializeComponent();
            this._gameClass = gameClass;
            this.gameController = GameController.NewGame();
            switch (this._gameClass) {
                case GameClass.WITH_AI:
                    prepareAIGameBoard();
                    break;
                case GameClass.WITH_HUMAN:
                    prepareHumanGameBoard();
                    break;
            }
            timer.Interval = 1000;
            timer.Tick += (obj, e) =>
            {
                this.lblRemainingTime.Text = 20 - (++passedTime) + " s";
                if (passedTime == 20)
                {
                    // time expired, lose
                    this.timer.Stop();
                    this._gameBoard.Lock();
                    DarkMessageBox.ShowInformation("Time expired. You lose.", "Time Expired");
                }
            };
        }

        GameController gameController;
        int passedTime = 0;

        private void prepareAIGameBoard()
        {
            this.lblTurn.ForeColor = Color.Green;
            this.lblTurn.Text = "Your Turn";
            this._gameBoard = new GameBoard(this.txtGameLog,
                new MoveHandler(
                    playerAIMove,
                    playerAIMove
                )
            );
            this.gameBoardPanel.Controls.Add(this._gameBoard);
            
            // start timer of 1 min
            timer.Start();
        }

        private bool playerAIMove(int x, int y)
        {
            // me move
            gameController.PlayerMove(y, x);
            this.txtGameLog.AppendText(_gameBoard.Step + "> Black moved at (" + x + ", " + y + ");\r\n");
            this._gameBoard.MovePiece(x, y);
            this.timer.Stop();

            // judge winner
            int winner = gameController.GetWinner();
            if (winner != 0)
            {
                _gameBoard.Lock();
                if (winner == 1)
                {
                    // black wins
                    this.lblTurn.Text = "Black Won";
                }
                else
                {
                    // white wins
                    this.lblTurn.Text = "White Won";
                }
                return false;
            }

            this.lblTurn.ForeColor = Color.Red;
            this.lblTurn.Text = "Machine's Turn";
            // ai move
            GameController.Point aiMove = gameController.AIMove();
            this.txtGameLog.AppendText(_gameBoard.Step + "> White moved at (" + aiMove.x + ", " + aiMove.y + ");\r\n");
            this._gameBoard.MovePiece(aiMove.y, aiMove.x);
            _gameBoard.UnLock();

            // judge winner
            winner = gameController.GetWinner();
            if (winner != 0)
            {
                _gameBoard.Lock();
                if (winner == 1)
                {
                    // black wins
                    this.lblTurn.Text = "Black Won";
                }
                else
                {
                    // white wins
                    this.lblTurn.Text = "White Won";
                }
                return false;
            }

            this.lblTurn.ForeColor = Color.Green;
            this.lblTurn.Text = "Your Turn";
            this.passedTime = 0;
            this.timer.Start();

            return true;
        }

        private void prepareHumanGameBoard()
        {
            // prepare state
            this.lblPlayerAName.Text = "Player A";
            this.lblPlayerBName.Text = "Player B";

            this.lblTurn.Text = "Player A's Turn";
            this.lblTurn.ForeColor = Color.Green;

            this._gameBoard = new GameBoard(this.txtGameLog,
                new MoveHandler(
                    (x, y) => {
                        // white move
                        gameController.PlayerMove(x, y);
                        this.txtGameLog.AppendText(_gameBoard.Step + "> Black moved at (" + x + ", " + y + ");\r\n");
                        this._gameBoard.MovePiece(x, y);
                        this.timer.Stop();

                        // judge winner
                        int winner = gameController.GetWinner();
                        if (winner != 0)
                        {
                            _gameBoard.Lock();
                            if (winner == 1)
                            {
                                // black wins
                                this.lblTurn.Text = "Black Won";
                            }
                            else
                            {
                                // white wins
                                this.lblTurn.Text = "White Won";
                            }
                            return false;
                        }
                        this.lblTurn.Text = "Player B's Turn";
                        this.lblTurn.ForeColor = Color.Blue;

                        this.passedTime = 0;
                        this.timer.Start();

                        return true;
                    },
                    (x, y) => {
                        // white move
                        gameController.PlayerMove(x, y);
                        this.txtGameLog.AppendText(_gameBoard.Step + "> White moved at (" + x + ", " + y + ");\r\n");
                        this._gameBoard.MovePiece(x, y);
                        this.timer.Stop();

                        // judge winner
                        int winner = gameController.GetWinner();
                        if (winner != 0)
                        {
                            _gameBoard.Lock();
                            if (winner == 1)
                            {
                                // black wins
                                this.lblTurn.Text = "Black Won";
                            }
                            else
                            {
                                // white wins
                                this.lblTurn.Text = "White Won";
                            }
                            return false;
                        }
                        this.lblTurn.Text = "Player A's Turn";
                        this.lblTurn.ForeColor = Color.Green;

                        this.passedTime = 0;
                        this.timer.Start();

                        return true;
                    }
                )
            );
            this.gameBoardPanel.Controls.Add(this._gameBoard);

            // start timer of 1 min
            timer.Start();
        }

        private void exitGobangToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnRestart_Click(object sender, EventArgs e)
        {
            this.gameController.RestartGame();
            // redraw
            this.gameBoardPanel.Controls.Clear();
            switch (this._gameClass)
            {
                case GameClass.WITH_AI:
                    prepareAIGameBoard();
                    break;
                case GameClass.WITH_HUMAN:
                    prepareHumanGameBoard();
                    break;
            }
            // rewind the clock
            this.passedTime = 0;
        }

        private void aboutGobangToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormAbout about = new FormAbout();
            about.ShowDialog();
        }

        private void FormGameBoard_Load(object sender, EventArgs e)
        {

        }

        private void gameToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }

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
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace gobang_gui.controllers
{
    class GameController
    {

        private IntPtr _gamePointer;
        private bool _isTrash = true;
        private int _winner = 0;
        public int Winner
        {
            get { return _winner; }
        }

        public struct Point
        {
            public int x;
            public int y;
            public Point(int x, int y)
            {
                this.x = x;
                this.y = y;
            }
        }

        public static GameController NewGame()
        {
            GameController controller = new GameController();
            controller._gamePointer = Interfaces._newGame();
            controller._isTrash = false;
            return controller;
        }

        public void RestartGame()
        {
            if (!this._isTrash)
            {
                Interfaces._restartGame(this._gamePointer);
            }
        }

        public void ReleaseGame()
        {
            if (!this._isTrash)
            {
                Interfaces._destroyGame(this._gamePointer);
                this._isTrash = true;
            }
        }

        public Point AIMove()
        {
            if (this._isTrash)
            {
                return new Point(0, 0);
            }
            Interfaces._aiMove(this._gamePointer);
            this._winner = Interfaces._getWinner(this._gamePointer);
            return new Point(
                Interfaces._getLastRow(this._gamePointer),
                Interfaces._getLastCol(this._gamePointer));
        }

        public bool PlayerMove(int r, int c)
        {
            if (this._isTrash)
            {
                return false;
            }
            bool isOK = Interfaces._playerMove(this._gamePointer, r, c) == 1;
            this._winner = Interfaces._getWinner(this._gamePointer);
            return isOK;
        }

        public int GetWinner()
        {
            if (this._isTrash)
            {
                return 0;
            }
            return Interfaces._getWinner(this._gamePointer);
        }
    }


}

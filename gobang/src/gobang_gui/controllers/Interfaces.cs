using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace gobang_gui.controllers
{
    public class Interfaces
    {
        [DllImport("libgobang.dll", EntryPoint = "NewGame", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr _newGame();

        [DllImport("libgobang.dll", EntryPoint = "AIMove", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _aiMove(IntPtr gamePtr);

        [DllImport("libgobang.dll", EntryPoint = "PlayerMove", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _playerMove(IntPtr gamePtr, int move_r, int move_c);

        [DllImport("libgobang.dll", EntryPoint = "DestroyGame", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _destroyGame(IntPtr gamePtr);

        [DllImport("libgobang.dll", EntryPoint = "GetWinner", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _getWinner(IntPtr gamePtr);

        [DllImport("libgobang.dll", EntryPoint = "GetLastRow", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _getLastRow(IntPtr gamePtr);

        [DllImport("libgobang.dll", EntryPoint = "GetLastCol", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _getLastCol(IntPtr gamePtr);

        [DllImport("libgobang.dll", EntryPoint = "GetCurrentPlayer", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _getCurrentPlayer(IntPtr gamePtr);

        [DllImport("libgobang.dll", EntryPoint = "RestartGame", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _restartGame(IntPtr gamePtr);
    }
}

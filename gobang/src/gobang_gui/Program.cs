using gobang_gui.forms;
using System;
using System.Windows.Forms;

namespace gobang_gui
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            FormWelcome welcome = new FormWelcome();
            welcome.ShowDialog();
            if (welcome.GetSelected() != null)
            {
                Application.Run(welcome.GetSelected());
            }
        }
    }
}

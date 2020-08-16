using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace gobang_gui.forms
{
    public partial class FormAbout : Form
    {
        public FormAbout()
        {
            InitializeComponent();
        }

        private void FormWelcome_Load(object sender, EventArgs e)
        {

        }

        Form selectedForm = null;

        private void btnStartAI_Click(object sender, EventArgs e)
        {
            selectedForm = new FormGameBoard(FormGameBoard.GameClass.WITH_AI);
            this.Close();
        }

        private void darkButton1_Click(object sender, EventArgs e)
        {
            selectedForm = new FormGameBoard(FormGameBoard.GameClass.WITH_HUMAN);
            this.Close();
        }

        public Form GetSelected()
        {
            return selectedForm;
        }
    }
}

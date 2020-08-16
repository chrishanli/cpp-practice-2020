namespace gobang_gui.forms
{
    partial class FormGameBoard
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormGameBoard));
            this.darkMenuStrip1 = new DarkUI.Controls.DarkMenuStrip();
            this.gameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitGobangToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutGobangToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.darkSectionPanel3 = new DarkUI.Controls.DarkSectionPanel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.lblRemainingTime = new DarkUI.Controls.DarkLabel();
            this.gameLogPanel = new DarkUI.Controls.DarkSectionPanel();
            this.txtGameLog = new DarkUI.Controls.DarkTextBox();
            this.darkSeparator2 = new DarkUI.Controls.DarkSeparator();
            this.darkSectionPanel1 = new DarkUI.Controls.DarkSectionPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.lblTurn = new DarkUI.Controls.DarkLabel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.lblPlayerBPiece = new DarkUI.Controls.DarkLabel();
            this.lblPlayerAPiece = new DarkUI.Controls.DarkLabel();
            this.lblPlayerAName = new DarkUI.Controls.DarkLabel();
            this.lblPlayerBName = new DarkUI.Controls.DarkLabel();
            this.darkSeparator1 = new DarkUI.Controls.DarkSeparator();
            this.gameBoardPanel = new System.Windows.Forms.Panel();
            this.darkSectionPanel2 = new DarkUI.Controls.DarkSectionPanel();
            this.btnRestart = new DarkUI.Controls.DarkButton();
            this.darkMenuStrip1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.darkSectionPanel3.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.gameLogPanel.SuspendLayout();
            this.darkSectionPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.darkSectionPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // darkMenuStrip1
            // 
            this.darkMenuStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.darkMenuStrip1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkMenuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.darkMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.gameToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.darkMenuStrip1.Location = new System.Drawing.Point(0, 0);
            this.darkMenuStrip1.Name = "darkMenuStrip1";
            this.darkMenuStrip1.Padding = new System.Windows.Forms.Padding(3, 2, 0, 2);
            this.darkMenuStrip1.Size = new System.Drawing.Size(842, 24);
            this.darkMenuStrip1.TabIndex = 0;
            this.darkMenuStrip1.Text = "darkMenuStrip1";
            // 
            // gameToolStripMenuItem
            // 
            this.gameToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.gameToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitGobangToolStripMenuItem});
            this.gameToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.gameToolStripMenuItem.Name = "gameToolStripMenuItem";
            this.gameToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.gameToolStripMenuItem.Text = "&Game";
            this.gameToolStripMenuItem.Click += new System.EventHandler(this.gameToolStripMenuItem_Click);
            // 
            // exitGobangToolStripMenuItem
            // 
            this.exitGobangToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.exitGobangToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.exitGobangToolStripMenuItem.Name = "exitGobangToolStripMenuItem";
            this.exitGobangToolStripMenuItem.Size = new System.Drawing.Size(168, 26);
            this.exitGobangToolStripMenuItem.Text = "&Exit Gobang";
            this.exitGobangToolStripMenuItem.Click += new System.EventHandler(this.exitGobangToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutGobangToolStripMenuItem});
            this.helpToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // aboutGobangToolStripMenuItem
            // 
            this.aboutGobangToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.aboutGobangToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.aboutGobangToolStripMenuItem.Name = "aboutGobangToolStripMenuItem";
            this.aboutGobangToolStripMenuItem.Size = new System.Drawing.Size(176, 26);
            this.aboutGobangToolStripMenuItem.Text = "&About Gobang";
            this.aboutGobangToolStripMenuItem.Click += new System.EventHandler(this.aboutGobangToolStripMenuItem_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 70F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel1.Controls.Add(this.panel1, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.gameBoardPanel, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(842, 589);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.darkSectionPanel2);
            this.panel1.Controls.Add(this.darkSectionPanel3);
            this.panel1.Controls.Add(this.gameLogPanel);
            this.panel1.Controls.Add(this.darkSectionPanel1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(592, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(247, 583);
            this.panel1.TabIndex = 1;
            // 
            // darkSectionPanel3
            // 
            this.darkSectionPanel3.Controls.Add(this.tableLayoutPanel4);
            this.darkSectionPanel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.darkSectionPanel3.Location = new System.Drawing.Point(0, 300);
            this.darkSectionPanel3.Name = "darkSectionPanel3";
            this.darkSectionPanel3.SectionHeader = "Remaining Time";
            this.darkSectionPanel3.Size = new System.Drawing.Size(247, 80);
            this.darkSectionPanel3.TabIndex = 3;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.ColumnCount = 1;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Controls.Add(this.lblRemainingTime, 0, 0);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(1, 25);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 1;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(245, 54);
            this.tableLayoutPanel4.TabIndex = 0;
            // 
            // lblRemainingTime
            // 
            this.lblRemainingTime.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblRemainingTime.AutoSize = true;
            this.lblRemainingTime.Font = new System.Drawing.Font("Lucida Sans", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblRemainingTime.ForeColor = System.Drawing.Color.White;
            this.lblRemainingTime.Location = new System.Drawing.Point(97, 16);
            this.lblRemainingTime.Name = "lblRemainingTime";
            this.lblRemainingTime.Size = new System.Drawing.Size(50, 22);
            this.lblRemainingTime.TabIndex = 4;
            this.lblRemainingTime.Text = "20 s";
            // 
            // gameLogPanel
            // 
            this.gameLogPanel.Controls.Add(this.txtGameLog);
            this.gameLogPanel.Controls.Add(this.darkSeparator2);
            this.gameLogPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.gameLogPanel.Location = new System.Drawing.Point(0, 150);
            this.gameLogPanel.Name = "gameLogPanel";
            this.gameLogPanel.SectionHeader = "Game Log";
            this.gameLogPanel.Size = new System.Drawing.Size(247, 150);
            this.gameLogPanel.TabIndex = 2;
            // 
            // txtGameLog
            // 
            this.txtGameLog.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.txtGameLog.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtGameLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtGameLog.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.txtGameLog.Location = new System.Drawing.Point(1, 27);
            this.txtGameLog.Multiline = true;
            this.txtGameLog.Name = "txtGameLog";
            this.txtGameLog.ReadOnly = true;
            this.txtGameLog.Size = new System.Drawing.Size(245, 122);
            this.txtGameLog.TabIndex = 1;
            // 
            // darkSeparator2
            // 
            this.darkSeparator2.Dock = System.Windows.Forms.DockStyle.Top;
            this.darkSeparator2.Location = new System.Drawing.Point(1, 25);
            this.darkSeparator2.Name = "darkSeparator2";
            this.darkSeparator2.Size = new System.Drawing.Size(245, 2);
            this.darkSeparator2.TabIndex = 0;
            this.darkSeparator2.Text = "darkSeparator2";
            // 
            // darkSectionPanel1
            // 
            this.darkSectionPanel1.Controls.Add(this.tableLayoutPanel2);
            this.darkSectionPanel1.Controls.Add(this.darkSeparator1);
            this.darkSectionPanel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.darkSectionPanel1.Location = new System.Drawing.Point(0, 0);
            this.darkSectionPanel1.Name = "darkSectionPanel1";
            this.darkSectionPanel1.SectionHeader = "Game Status";
            this.darkSectionPanel1.Size = new System.Drawing.Size(247, 150);
            this.darkSectionPanel1.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.lblTurn, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel3, 0, 1);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(1, 27);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(245, 122);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // lblTurn
            // 
            this.lblTurn.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblTurn.AutoSize = true;
            this.lblTurn.Font = new System.Drawing.Font("Lucida Sans", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTurn.ForeColor = System.Drawing.Color.Green;
            this.lblTurn.Location = new System.Drawing.Point(70, 13);
            this.lblTurn.Name = "lblTurn";
            this.lblTurn.Size = new System.Drawing.Size(104, 22);
            this.lblTurn.TabIndex = 2;
            this.lblTurn.Text = "Your Turn";
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.lblPlayerBPiece, 1, 1);
            this.tableLayoutPanel3.Controls.Add(this.lblPlayerAPiece, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.lblPlayerAName, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.lblPlayerBName, 0, 1);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 51);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 2;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(239, 68);
            this.tableLayoutPanel3.TabIndex = 3;
            // 
            // lblPlayerBPiece
            // 
            this.lblPlayerBPiece.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblPlayerBPiece.AutoSize = true;
            this.lblPlayerBPiece.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.lblPlayerBPiece.Location = new System.Drawing.Point(122, 43);
            this.lblPlayerBPiece.Name = "lblPlayerBPiece";
            this.lblPlayerBPiece.Size = new System.Drawing.Size(47, 15);
            this.lblPlayerBPiece.TabIndex = 3;
            this.lblPlayerBPiece.Text = "White";
            // 
            // lblPlayerAPiece
            // 
            this.lblPlayerAPiece.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblPlayerAPiece.AutoSize = true;
            this.lblPlayerAPiece.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.lblPlayerAPiece.Location = new System.Drawing.Point(122, 9);
            this.lblPlayerAPiece.Name = "lblPlayerAPiece";
            this.lblPlayerAPiece.Size = new System.Drawing.Size(47, 15);
            this.lblPlayerAPiece.TabIndex = 2;
            this.lblPlayerAPiece.Text = "Black";
            this.lblPlayerAPiece.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblPlayerAName
            // 
            this.lblPlayerAName.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.lblPlayerAName.AutoSize = true;
            this.lblPlayerAName.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.lblPlayerAName.Location = new System.Drawing.Point(77, 9);
            this.lblPlayerAName.Name = "lblPlayerAName";
            this.lblPlayerAName.Size = new System.Drawing.Size(39, 15);
            this.lblPlayerAName.TabIndex = 0;
            this.lblPlayerAName.Text = "You:";
            // 
            // lblPlayerBName
            // 
            this.lblPlayerBName.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.lblPlayerBName.AutoSize = true;
            this.lblPlayerBName.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.lblPlayerBName.Location = new System.Drawing.Point(37, 43);
            this.lblPlayerBName.Name = "lblPlayerBName";
            this.lblPlayerBName.Size = new System.Drawing.Size(79, 15);
            this.lblPlayerBName.TabIndex = 1;
            this.lblPlayerBName.Text = "Opponent:";
            // 
            // darkSeparator1
            // 
            this.darkSeparator1.Dock = System.Windows.Forms.DockStyle.Top;
            this.darkSeparator1.Location = new System.Drawing.Point(1, 25);
            this.darkSeparator1.Name = "darkSeparator1";
            this.darkSeparator1.Size = new System.Drawing.Size(245, 2);
            this.darkSeparator1.TabIndex = 0;
            this.darkSeparator1.Text = "darkSeparator1";
            // 
            // gameBoardPanel
            // 
            this.gameBoardPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gameBoardPanel.Location = new System.Drawing.Point(3, 3);
            this.gameBoardPanel.Name = "gameBoardPanel";
            this.gameBoardPanel.Size = new System.Drawing.Size(583, 583);
            this.gameBoardPanel.TabIndex = 2;
            // 
            // darkSectionPanel2
            // 
            this.darkSectionPanel2.Controls.Add(this.btnRestart);
            this.darkSectionPanel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.darkSectionPanel2.Location = new System.Drawing.Point(0, 380);
            this.darkSectionPanel2.Name = "darkSectionPanel2";
            this.darkSectionPanel2.SectionHeader = "Game Control";
            this.darkSectionPanel2.Size = new System.Drawing.Size(247, 80);
            this.darkSectionPanel2.TabIndex = 4;
            // 
            // btnRestart
            // 
            this.btnRestart.Location = new System.Drawing.Point(66, 39);
            this.btnRestart.Name = "btnRestart";
            this.btnRestart.Padding = new System.Windows.Forms.Padding(5);
            this.btnRestart.Size = new System.Drawing.Size(107, 23);
            this.btnRestart.TabIndex = 1;
            this.btnRestart.Text = "Restart";
            this.btnRestart.Click += new System.EventHandler(this.btnRestart_Click);
            // 
            // FormGameBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.ClientSize = new System.Drawing.Size(842, 613);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.darkMenuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.darkMenuStrip1;
            this.Name = "FormGameBoard";
            this.Text = "Gobang Game Board";
            this.Load += new System.EventHandler(this.FormGameBoard_Load);
            this.darkMenuStrip1.ResumeLayout(false);
            this.darkMenuStrip1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.darkSectionPanel3.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.gameLogPanel.ResumeLayout(false);
            this.gameLogPanel.PerformLayout();
            this.darkSectionPanel1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.darkSectionPanel2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DarkUI.Controls.DarkMenuStrip darkMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem gameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitGobangToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutGobangToolStripMenuItem;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel panel1;
        private DarkUI.Controls.DarkSectionPanel darkSectionPanel1;
        private DarkUI.Controls.DarkSeparator darkSeparator1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private DarkUI.Controls.DarkLabel lblTurn;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private DarkUI.Controls.DarkLabel lblPlayerAName;
        private DarkUI.Controls.DarkLabel lblPlayerBName;
        private DarkUI.Controls.DarkLabel lblPlayerBPiece;
        private DarkUI.Controls.DarkLabel lblPlayerAPiece;
        private System.Windows.Forms.Panel gameBoardPanel;
        private DarkUI.Controls.DarkSectionPanel gameLogPanel;
        private DarkUI.Controls.DarkSeparator darkSeparator2;
        private DarkUI.Controls.DarkTextBox txtGameLog;
        private DarkUI.Controls.DarkSectionPanel darkSectionPanel3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private DarkUI.Controls.DarkLabel lblRemainingTime;
        private DarkUI.Controls.DarkSectionPanel darkSectionPanel2;
        private DarkUI.Controls.DarkButton btnRestart;
    }
}


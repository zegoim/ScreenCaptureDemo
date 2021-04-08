namespace ZegoScreenCapture_.net_
{
    partial class Form1
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
            this.radioButtonScreen = new System.Windows.Forms.RadioButton();
            this.target_group = new System.Windows.Forms.GroupBox();
            this.buttonRefreshScreen = new System.Windows.Forms.Button();
            this.buttonCapture = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonView = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonThumbnail = new System.Windows.Forms.Button();
            this.labelW = new System.Windows.Forms.Label();
            this.labelH = new System.Windows.Forms.Label();
            this.labelY = new System.Windows.Forms.Label();
            this.labelX = new System.Windows.Forms.Label();
            this.trackBarW = new System.Windows.Forms.TrackBar();
            this.trackBarH = new System.Windows.Forms.TrackBar();
            this.trackBarY = new System.Windows.Forms.TrackBar();
            this.trackBarX = new System.Windows.Forms.TrackBar();
            this.buttonRefreshWindow = new System.Windows.Forms.Button();
            this.comboBoxWindow = new System.Windows.Forms.ComboBox();
            this.comboBoxScreen = new System.Windows.Forms.ComboBox();
            this.radioButtonRect = new System.Windows.Forms.RadioButton();
            this.radioButtonWindow = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.labelFPS = new System.Windows.Forms.Label();
            this.labelBitrate = new System.Windows.Forms.Label();
            this.buttonRemoveCaptureWindow = new System.Windows.Forms.Button();
            this.buttonAddCaptureWindow = new System.Windows.Forms.Button();
            this.buttonRemoveExcludeWindow = new System.Windows.Forms.Button();
            this.buttonAddExcludeWindow = new System.Windows.Forms.Button();
            this.comboBoxWindow2 = new System.Windows.Forms.ComboBox();
            this.checkBoxClickanimation = new System.Windows.Forms.CheckBox();
            this.checkBoxCursor = new System.Windows.Forms.CheckBox();
            this.trackBarFPS = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.trackBarBitrate = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBoxResolution = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.richTextBoxMsg = new System.Windows.Forms.RichTextBox();
            this.textBoxHlsUrl = new System.Windows.Forms.TextBox();
            this.buttonPublish = new System.Windows.Forms.Button();
            this.textBoxRtmpUrl = new System.Windows.Forms.TextBox();
            this.target_group.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarX)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarFPS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBitrate)).BeginInit();
            this.SuspendLayout();
            // 
            // radioButtonScreen
            // 
            this.radioButtonScreen.AutoSize = true;
            this.radioButtonScreen.Location = new System.Drawing.Point(17, 30);
            this.radioButtonScreen.Name = "radioButtonScreen";
            this.radioButtonScreen.Size = new System.Drawing.Size(47, 16);
            this.radioButtonScreen.TabIndex = 0;
            this.radioButtonScreen.TabStop = true;
            this.radioButtonScreen.Text = "屏幕";
            this.radioButtonScreen.UseVisualStyleBackColor = true;
            this.radioButtonScreen.CheckedChanged += new System.EventHandler(this.radioButtonScreen_CheckedChanged);
            // 
            // target_group
            // 
            this.target_group.Controls.Add(this.buttonRefreshScreen);
            this.target_group.Controls.Add(this.buttonCapture);
            this.target_group.Controls.Add(this.textBox1);
            this.target_group.Controls.Add(this.buttonView);
            this.target_group.Controls.Add(this.label1);
            this.target_group.Controls.Add(this.buttonThumbnail);
            this.target_group.Controls.Add(this.labelW);
            this.target_group.Controls.Add(this.labelH);
            this.target_group.Controls.Add(this.labelY);
            this.target_group.Controls.Add(this.labelX);
            this.target_group.Controls.Add(this.trackBarW);
            this.target_group.Controls.Add(this.trackBarH);
            this.target_group.Controls.Add(this.trackBarY);
            this.target_group.Controls.Add(this.trackBarX);
            this.target_group.Controls.Add(this.buttonRefreshWindow);
            this.target_group.Controls.Add(this.comboBoxWindow);
            this.target_group.Controls.Add(this.comboBoxScreen);
            this.target_group.Controls.Add(this.radioButtonRect);
            this.target_group.Controls.Add(this.radioButtonWindow);
            this.target_group.Controls.Add(this.radioButtonScreen);
            this.target_group.Location = new System.Drawing.Point(12, 12);
            this.target_group.Name = "target_group";
            this.target_group.Size = new System.Drawing.Size(360, 297);
            this.target_group.TabIndex = 1;
            this.target_group.TabStop = false;
            this.target_group.Text = "分享目标";
            // 
            // buttonRefreshScreen
            // 
            this.buttonRefreshScreen.Location = new System.Drawing.Point(267, 32);
            this.buttonRefreshScreen.Name = "buttonRefreshScreen";
            this.buttonRefreshScreen.Size = new System.Drawing.Size(61, 23);
            this.buttonRefreshScreen.TabIndex = 16;
            this.buttonRefreshScreen.Text = "刷新";
            this.buttonRefreshScreen.UseVisualStyleBackColor = true;
            this.buttonRefreshScreen.Click += new System.EventHandler(this.buttonRefreshScreen_Click);
            // 
            // buttonCapture
            // 
            this.buttonCapture.Location = new System.Drawing.Point(233, 258);
            this.buttonCapture.Name = "buttonCapture";
            this.buttonCapture.Size = new System.Drawing.Size(100, 23);
            this.buttonCapture.TabIndex = 9;
            this.buttonCapture.Text = "开始采集";
            this.buttonCapture.UseVisualStyleBackColor = true;
            this.buttonCapture.Click += new System.EventHandler(this.buttonCapture_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(98, 220);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 15;
            // 
            // buttonView
            // 
            this.buttonView.Location = new System.Drawing.Point(123, 258);
            this.buttonView.Name = "buttonView";
            this.buttonView.Size = new System.Drawing.Size(100, 23);
            this.buttonView.TabIndex = 8;
            this.buttonView.Text = "采集预览";
            this.buttonView.UseVisualStyleBackColor = true;
            this.buttonView.Click += new System.EventHandler(this.buttonView_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 223);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 14;
            this.label1.Text = "窗口采集模式";
            // 
            // buttonThumbnail
            // 
            this.buttonThumbnail.Location = new System.Drawing.Point(17, 258);
            this.buttonThumbnail.Name = "buttonThumbnail";
            this.buttonThumbnail.Size = new System.Drawing.Size(100, 23);
            this.buttonThumbnail.TabIndex = 7;
            this.buttonThumbnail.Text = "缩略图预览";
            this.buttonThumbnail.UseVisualStyleBackColor = true;
            this.buttonThumbnail.Click += new System.EventHandler(this.buttonThumbnail_Click);
            // 
            // labelW
            // 
            this.labelW.AutoSize = true;
            this.labelW.Location = new System.Drawing.Point(186, 176);
            this.labelW.Name = "labelW";
            this.labelW.Size = new System.Drawing.Size(11, 12);
            this.labelW.TabIndex = 13;
            this.labelW.Text = "W";
            // 
            // labelH
            // 
            this.labelH.AutoSize = true;
            this.labelH.Location = new System.Drawing.Point(17, 176);
            this.labelH.Name = "labelH";
            this.labelH.Size = new System.Drawing.Size(11, 12);
            this.labelH.TabIndex = 12;
            this.labelH.Text = "H";
            // 
            // labelY
            // 
            this.labelY.AutoSize = true;
            this.labelY.Location = new System.Drawing.Point(186, 143);
            this.labelY.Name = "labelY";
            this.labelY.Size = new System.Drawing.Size(11, 12);
            this.labelY.TabIndex = 11;
            this.labelY.Text = "Y";
            // 
            // labelX
            // 
            this.labelX.AutoSize = true;
            this.labelX.Location = new System.Drawing.Point(17, 143);
            this.labelX.Name = "labelX";
            this.labelX.Size = new System.Drawing.Size(11, 12);
            this.labelX.TabIndex = 10;
            this.labelX.Text = "X";
            // 
            // trackBarW
            // 
            this.trackBarW.Location = new System.Drawing.Point(233, 176);
            this.trackBarW.Name = "trackBarW";
            this.trackBarW.Size = new System.Drawing.Size(104, 45);
            this.trackBarW.TabIndex = 9;
            this.trackBarW.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBarW.Scroll += new System.EventHandler(this.trackBarW_Scroll);
            // 
            // trackBarH
            // 
            this.trackBarH.Location = new System.Drawing.Point(63, 175);
            this.trackBarH.Name = "trackBarH";
            this.trackBarH.Size = new System.Drawing.Size(104, 45);
            this.trackBarH.TabIndex = 8;
            this.trackBarH.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBarH.Scroll += new System.EventHandler(this.trackBarH_Scroll);
            // 
            // trackBarY
            // 
            this.trackBarY.Location = new System.Drawing.Point(233, 143);
            this.trackBarY.Name = "trackBarY";
            this.trackBarY.Size = new System.Drawing.Size(104, 45);
            this.trackBarY.TabIndex = 6;
            this.trackBarY.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBarY.Scroll += new System.EventHandler(this.trackBarY_Scroll);
            // 
            // trackBarX
            // 
            this.trackBarX.Location = new System.Drawing.Point(63, 143);
            this.trackBarX.Name = "trackBarX";
            this.trackBarX.Size = new System.Drawing.Size(104, 45);
            this.trackBarX.TabIndex = 2;
            this.trackBarX.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBarX.Scroll += new System.EventHandler(this.trackBarX_Scroll);
            // 
            // buttonRefreshWindow
            // 
            this.buttonRefreshWindow.Location = new System.Drawing.Point(267, 69);
            this.buttonRefreshWindow.Name = "buttonRefreshWindow";
            this.buttonRefreshWindow.Size = new System.Drawing.Size(61, 23);
            this.buttonRefreshWindow.TabIndex = 5;
            this.buttonRefreshWindow.Text = "刷新";
            this.buttonRefreshWindow.UseVisualStyleBackColor = true;
            this.buttonRefreshWindow.Click += new System.EventHandler(this.buttonRefreshWindow_Click);
            // 
            // comboBoxWindow
            // 
            this.comboBoxWindow.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxWindow.FormattingEnabled = true;
            this.comboBoxWindow.Location = new System.Drawing.Point(82, 69);
            this.comboBoxWindow.Name = "comboBoxWindow";
            this.comboBoxWindow.Size = new System.Drawing.Size(169, 20);
            this.comboBoxWindow.TabIndex = 4;
            this.comboBoxWindow.SelectedIndexChanged += new System.EventHandler(this.comboBoxWindow_SelectedIndexChanged);
            // 
            // comboBoxScreen
            // 
            this.comboBoxScreen.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxScreen.FormattingEnabled = true;
            this.comboBoxScreen.Location = new System.Drawing.Point(82, 34);
            this.comboBoxScreen.Name = "comboBoxScreen";
            this.comboBoxScreen.Size = new System.Drawing.Size(169, 20);
            this.comboBoxScreen.TabIndex = 3;
            this.comboBoxScreen.SelectedIndexChanged += new System.EventHandler(this.comboBoxScreen_SelectedIndexChanged);
            // 
            // radioButtonRect
            // 
            this.radioButtonRect.AutoSize = true;
            this.radioButtonRect.Location = new System.Drawing.Point(17, 110);
            this.radioButtonRect.Name = "radioButtonRect";
            this.radioButtonRect.Size = new System.Drawing.Size(47, 16);
            this.radioButtonRect.TabIndex = 2;
            this.radioButtonRect.TabStop = true;
            this.radioButtonRect.Text = "区域";
            this.radioButtonRect.UseVisualStyleBackColor = true;
            this.radioButtonRect.CheckedChanged += new System.EventHandler(this.radioButtonRect_CheckedChanged);
            // 
            // radioButtonWindow
            // 
            this.radioButtonWindow.AutoSize = true;
            this.radioButtonWindow.Location = new System.Drawing.Point(17, 69);
            this.radioButtonWindow.Name = "radioButtonWindow";
            this.radioButtonWindow.Size = new System.Drawing.Size(47, 16);
            this.radioButtonWindow.TabIndex = 1;
            this.radioButtonWindow.TabStop = true;
            this.radioButtonWindow.Text = "窗口";
            this.radioButtonWindow.UseVisualStyleBackColor = true;
            this.radioButtonWindow.CheckedChanged += new System.EventHandler(this.radioButtonWindow_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.labelFPS);
            this.groupBox1.Controls.Add(this.labelBitrate);
            this.groupBox1.Controls.Add(this.buttonRemoveCaptureWindow);
            this.groupBox1.Controls.Add(this.buttonAddCaptureWindow);
            this.groupBox1.Controls.Add(this.buttonRemoveExcludeWindow);
            this.groupBox1.Controls.Add(this.buttonAddExcludeWindow);
            this.groupBox1.Controls.Add(this.comboBoxWindow2);
            this.groupBox1.Controls.Add(this.checkBoxClickanimation);
            this.groupBox1.Controls.Add(this.checkBoxCursor);
            this.groupBox1.Controls.Add(this.trackBarFPS);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.trackBarBitrate);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.comboBoxResolution);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(389, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(281, 297);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "推流 | 杂项设置";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // labelFPS
            // 
            this.labelFPS.AutoSize = true;
            this.labelFPS.Location = new System.Drawing.Point(225, 114);
            this.labelFPS.Name = "labelFPS";
            this.labelFPS.Size = new System.Drawing.Size(0, 12);
            this.labelFPS.TabIndex = 20;
            // 
            // labelBitrate
            // 
            this.labelBitrate.AutoSize = true;
            this.labelBitrate.Location = new System.Drawing.Point(225, 73);
            this.labelBitrate.Name = "labelBitrate";
            this.labelBitrate.Size = new System.Drawing.Size(0, 12);
            this.labelBitrate.TabIndex = 19;
            // 
            // buttonRemoveCaptureWindow
            // 
            this.buttonRemoveCaptureWindow.Location = new System.Drawing.Point(156, 258);
            this.buttonRemoveCaptureWindow.Name = "buttonRemoveCaptureWindow";
            this.buttonRemoveCaptureWindow.Size = new System.Drawing.Size(110, 23);
            this.buttonRemoveCaptureWindow.TabIndex = 18;
            this.buttonRemoveCaptureWindow.Text = "移除采集窗口";
            this.buttonRemoveCaptureWindow.UseVisualStyleBackColor = true;
            this.buttonRemoveCaptureWindow.Click += new System.EventHandler(this.buttonRemoveCaptureWindow_Click);
            // 
            // buttonAddCaptureWindow
            // 
            this.buttonAddCaptureWindow.Location = new System.Drawing.Point(20, 258);
            this.buttonAddCaptureWindow.Name = "buttonAddCaptureWindow";
            this.buttonAddCaptureWindow.Size = new System.Drawing.Size(110, 23);
            this.buttonAddCaptureWindow.TabIndex = 17;
            this.buttonAddCaptureWindow.Text = "添加采集窗口";
            this.buttonAddCaptureWindow.UseVisualStyleBackColor = true;
            this.buttonAddCaptureWindow.Click += new System.EventHandler(this.buttonAddCaptureWindow_Click);
            // 
            // buttonRemoveExcludeWindow
            // 
            this.buttonRemoveExcludeWindow.Location = new System.Drawing.Point(156, 223);
            this.buttonRemoveExcludeWindow.Name = "buttonRemoveExcludeWindow";
            this.buttonRemoveExcludeWindow.Size = new System.Drawing.Size(110, 23);
            this.buttonRemoveExcludeWindow.TabIndex = 16;
            this.buttonRemoveExcludeWindow.Text = "移除过滤窗口";
            this.buttonRemoveExcludeWindow.UseVisualStyleBackColor = true;
            this.buttonRemoveExcludeWindow.Click += new System.EventHandler(this.buttonRemoveExcludeWindow_Click);
            // 
            // buttonAddExcludeWindow
            // 
            this.buttonAddExcludeWindow.Location = new System.Drawing.Point(20, 223);
            this.buttonAddExcludeWindow.Name = "buttonAddExcludeWindow";
            this.buttonAddExcludeWindow.Size = new System.Drawing.Size(110, 23);
            this.buttonAddExcludeWindow.TabIndex = 15;
            this.buttonAddExcludeWindow.Text = "添加过滤窗口";
            this.buttonAddExcludeWindow.UseVisualStyleBackColor = true;
            this.buttonAddExcludeWindow.Click += new System.EventHandler(this.buttonAddExcludeWindow_Click);
            // 
            // comboBoxWindow2
            // 
            this.comboBoxWindow2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxWindow2.FormattingEnabled = true;
            this.comboBoxWindow2.Location = new System.Drawing.Point(20, 187);
            this.comboBoxWindow2.Name = "comboBoxWindow2";
            this.comboBoxWindow2.Size = new System.Drawing.Size(246, 20);
            this.comboBoxWindow2.TabIndex = 14;
            // 
            // checkBoxClickanimation
            // 
            this.checkBoxClickanimation.AutoSize = true;
            this.checkBoxClickanimation.Location = new System.Drawing.Point(116, 154);
            this.checkBoxClickanimation.Name = "checkBoxClickanimation";
            this.checkBoxClickanimation.Size = new System.Drawing.Size(96, 16);
            this.checkBoxClickanimation.TabIndex = 13;
            this.checkBoxClickanimation.Text = "显示点击动画";
            this.checkBoxClickanimation.UseVisualStyleBackColor = true;
            this.checkBoxClickanimation.CheckedChanged += new System.EventHandler(this.checkBoxClickanimation_CheckedChanged);
            // 
            // checkBoxCursor
            // 
            this.checkBoxCursor.AutoSize = true;
            this.checkBoxCursor.Location = new System.Drawing.Point(20, 154);
            this.checkBoxCursor.Name = "checkBoxCursor";
            this.checkBoxCursor.Size = new System.Drawing.Size(72, 16);
            this.checkBoxCursor.TabIndex = 12;
            this.checkBoxCursor.Text = "显示鼠标";
            this.checkBoxCursor.UseVisualStyleBackColor = true;
            this.checkBoxCursor.CheckedChanged += new System.EventHandler(this.checkBoxCursor_CheckedChanged);
            // 
            // trackBarFPS
            // 
            this.trackBarFPS.Location = new System.Drawing.Point(70, 110);
            this.trackBarFPS.Name = "trackBarFPS";
            this.trackBarFPS.Size = new System.Drawing.Size(151, 45);
            this.trackBarFPS.TabIndex = 11;
            this.trackBarFPS.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBarFPS.Scroll += new System.EventHandler(this.trackBarFPS_Scroll);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 10;
            this.label4.Text = "帧率";
            // 
            // trackBarBitrate
            // 
            this.trackBarBitrate.Location = new System.Drawing.Point(70, 69);
            this.trackBarBitrate.Name = "trackBarBitrate";
            this.trackBarBitrate.Size = new System.Drawing.Size(151, 45);
            this.trackBarBitrate.TabIndex = 9;
            this.trackBarBitrate.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBarBitrate.Scroll += new System.EventHandler(this.trackBarBitrate_Scroll);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 71);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "码率";
            // 
            // comboBoxResolution
            // 
            this.comboBoxResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxResolution.FormattingEnabled = true;
            this.comboBoxResolution.Location = new System.Drawing.Point(77, 29);
            this.comboBoxResolution.Name = "comboBoxResolution";
            this.comboBoxResolution.Size = new System.Drawing.Size(189, 20);
            this.comboBoxResolution.TabIndex = 1;
            this.comboBoxResolution.SelectedIndexChanged += new System.EventHandler(this.comboBoxResolution_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "分辨率";
            // 
            // richTextBoxMsg
            // 
            this.richTextBoxMsg.Location = new System.Drawing.Point(13, 315);
            this.richTextBoxMsg.Name = "richTextBoxMsg";
            this.richTextBoxMsg.Size = new System.Drawing.Size(656, 140);
            this.richTextBoxMsg.TabIndex = 3;
            this.richTextBoxMsg.Text = "";
            this.richTextBoxMsg.TextChanged += new System.EventHandler(this.richTextBoxMsg_TextChanged);
            // 
            // textBoxHlsUrl
            // 
            this.textBoxHlsUrl.Location = new System.Drawing.Point(13, 489);
            this.textBoxHlsUrl.Name = "textBoxHlsUrl";
            this.textBoxHlsUrl.Size = new System.Drawing.Size(545, 21);
            this.textBoxHlsUrl.TabIndex = 5;
            // 
            // buttonPublish
            // 
            this.buttonPublish.Location = new System.Drawing.Point(565, 471);
            this.buttonPublish.Name = "buttonPublish";
            this.buttonPublish.Size = new System.Drawing.Size(90, 38);
            this.buttonPublish.TabIndex = 6;
            this.buttonPublish.Text = "开始推流";
            this.buttonPublish.UseVisualStyleBackColor = true;
            this.buttonPublish.Click += new System.EventHandler(this.buttonPublish_Click);
            // 
            // textBoxRtmpUrl
            // 
            this.textBoxRtmpUrl.Location = new System.Drawing.Point(13, 461);
            this.textBoxRtmpUrl.Name = "textBoxRtmpUrl";
            this.textBoxRtmpUrl.Size = new System.Drawing.Size(545, 21);
            this.textBoxRtmpUrl.TabIndex = 4;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(681, 521);
            this.Controls.Add(this.buttonPublish);
            this.Controls.Add(this.textBoxHlsUrl);
            this.Controls.Add(this.textBoxRtmpUrl);
            this.Controls.Add(this.richTextBoxMsg);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.target_group);
            this.Name = "Form1";
            this.Text = "ScreenCaptureDemo";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form_Closing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form_Closed);
            this.target_group.ResumeLayout(false);
            this.target_group.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarX)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarFPS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBitrate)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton radioButtonScreen;
        private System.Windows.Forms.GroupBox target_group;
        private System.Windows.Forms.RadioButton radioButtonRect;
        private System.Windows.Forms.RadioButton radioButtonWindow;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelW;
        private System.Windows.Forms.Label labelH;
        private System.Windows.Forms.Label labelY;
        private System.Windows.Forms.Label labelX;
        private System.Windows.Forms.TrackBar trackBarW;
        private System.Windows.Forms.TrackBar trackBarH;
        private System.Windows.Forms.TrackBar trackBarY;
        private System.Windows.Forms.TrackBar trackBarX;
        private System.Windows.Forms.Button buttonRefreshWindow;
        private System.Windows.Forms.ComboBox comboBoxWindow;
        private System.Windows.Forms.ComboBox comboBoxScreen;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonRemoveCaptureWindow;
        private System.Windows.Forms.Button buttonAddCaptureWindow;
        private System.Windows.Forms.Button buttonRemoveExcludeWindow;
        private System.Windows.Forms.Button buttonAddExcludeWindow;
        private System.Windows.Forms.ComboBox comboBoxWindow2;
        private System.Windows.Forms.CheckBox checkBoxClickanimation;
        private System.Windows.Forms.CheckBox checkBoxCursor;
        private System.Windows.Forms.TrackBar trackBarFPS;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar trackBarBitrate;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxResolution;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RichTextBox richTextBoxMsg;
        private System.Windows.Forms.TextBox textBoxHlsUrl;
        private System.Windows.Forms.Button buttonPublish;
        private System.Windows.Forms.TextBox textBoxRtmpUrl;
        private System.Windows.Forms.Button buttonCapture;
        private System.Windows.Forms.Button buttonView;
        private System.Windows.Forms.Button buttonThumbnail;
        private System.Windows.Forms.Button buttonRefreshScreen;
        private System.Windows.Forms.Label labelFPS;
        private System.Windows.Forms.Label labelBitrate;
    }
}


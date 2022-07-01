using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace ZegoScreenCapture_.net_
{
    public partial class Form1 : Form
    {
        List<Tuple<int, int>> m_resolutions = new List<Tuple<int, int>>();
        List<IntPtr> m_windows = new List<IntPtr>();
        List<IntPtr> m_windows2 = new List<IntPtr>();

        string m_userID = "123456";
        string m_userName = "ScreenCaptureDemo";
        string m_roomID = "123456";

        uint m_appiId = 1;
        string m_appSign = ;

        //屏幕采集的回调对象
        ScreenCaptureManager.zego_screencapture_capture_error_notify_func m_zego_screencapture_capture_error_notify;
        ScreenCaptureManager.zego_screencapture_capture_process_window_change_notify_func m_zego_screencapture_capture_process_window_change_notify;
        ScreenCaptureManager.zego_screencapture_mutiple_captured_frame_available_notify_func m_zego_screencapture_mutiple_captured_frame_available_notify;
        ScreenCaptureManager.zego_screencapture_capture_dwm_composition_change_notify_func m_zego_screencapture_capture_dwm_composition_change_notify;
        ScreenCaptureManager.zego_screencapture_captured_window_status_change_notify_func m_zego_screencapture_captured_window_status_change_notify;
        ScreenCaptureManager.zego_screencapture_captured_frame_available_notify_func m_zego_screencapture_captured_frame_available_notify;

        //Express的回调对象
        ExpressManager.zego_on_engine_state_update m_zego_on_engine_state_update;
        ExpressManager.zego_on_room_state_update m_zego_on_room_state_update;
        ExpressManager.zego_on_engine_uninit m_zego_on_engine_uninit;
        ExpressManager.zego_on_publisher_state_update m_zego_on_publisher_state_update;
        ExpressManager.zego_on_publisher_quality_update m_zego_on_publisher_quality_update;

        ScreenCaptureView m_screenCaptureView = new ScreenCaptureView();

        public Form1()
        {
            InitializeComponent();
            InitExpress();
            InitScreenCapture();
            InitUI();
            
        }

        private void InitExpress()
        {
            //初始化Express回调对象
            m_zego_on_engine_state_update = new ExpressManager.zego_on_engine_state_update(zego_on_engine_state_update);
            m_zego_on_room_state_update = new ExpressManager.zego_on_room_state_update(zego_on_room_state_update);
            m_zego_on_engine_uninit = new ExpressManager.zego_on_engine_uninit(zego_on_engine_uninit);
            m_zego_on_publisher_state_update = new ExpressManager.zego_on_publisher_state_update(zego_on_publisher_state_update);
            m_zego_on_publisher_quality_update = new ExpressManager.zego_on_publisher_quality_update(zego_on_publisher_quality_update);
            ExpressManager.zego_register_engine_state_update_callback(m_zego_on_engine_state_update, IntPtr.Zero);
            ExpressManager.zego_register_room_state_update_callback(m_zego_on_room_state_update, IntPtr.Zero);
            ExpressManager.zego_register_engine_uninit_callback(m_zego_on_engine_uninit, IntPtr.Zero);
            ExpressManager.zego_register_publisher_state_update_callback(m_zego_on_publisher_state_update, IntPtr.Zero);
            ExpressManager.zego_register_publisher_quality_update_callback(m_zego_on_publisher_quality_update, IntPtr.Zero);
            ExpressManager.zego_express_set_platform_language(zego_platform_language.zego_platform_language_c);

            zego_engine_config engine_config = new zego_engine_config();

            zego_log_config logConfig = new zego_log_config();
            logConfig.log_path = System.Windows.Forms.Application.StartupPath + "\\";
            logConfig.log_size = 5 * 1024 * 1024;

            engine_config.log_config = Marshal.AllocHGlobal(Marshal.SizeOf(logConfig));
            Marshal.StructureToPtr(logConfig, engine_config.log_config, false);

            ExpressManager.zego_express_set_engine_config(engine_config);

            ExpressManager.zego_express_set_log_config(logConfig);

            zego_engine_profile profile = new zego_engine_profile();
            profile.app_sign = new char[64];
            profile.app_id = m_appiId;
            for(int i=0;i<m_appSign.Length;i++)
            {
                profile.app_sign[i] = m_appSign[i];
            }

            profile.scenario = zego_scenario.zego_scenario_general;

            int result = ExpressManager.zego_express_engine_init_with_profile(profile);

            zego_custom_video_capture_config custom_video_capture_config = new zego_custom_video_capture_config();
            custom_video_capture_config.buffer_type = zego_video_buffer_type.zego_video_buffer_type_raw_data;
            ExpressManager.zego_express_enable_custom_video_capture(true, ref custom_video_capture_config, zego_publish_channel.zego_publish_channel_main);


            zego_user user = new zego_user();
            user.user_id = m_userID;
            user.user_name = m_userName;

            ExpressManager.zego_express_login_room(m_roomID, user, IntPtr.Zero);
        }

        private void InitScreenCapture()
        {
            //初始化屏幕采集回调对象
            m_zego_screencapture_capture_error_notify = new ScreenCaptureManager.zego_screencapture_capture_error_notify_func(zego_screencapture_capture_error_notify);
            m_zego_screencapture_capture_process_window_change_notify = new ScreenCaptureManager.zego_screencapture_capture_process_window_change_notify_func(zego_screencapture_capture_process_window_change_notify);
            m_zego_screencapture_mutiple_captured_frame_available_notify = new ScreenCaptureManager.zego_screencapture_mutiple_captured_frame_available_notify_func(zego_screencapture_mutiple_captured_frame_available_notify);
            m_zego_screencapture_captured_window_status_change_notify = new ScreenCaptureManager.zego_screencapture_captured_window_status_change_notify_func(zego_screencapture_captured_window_status_change_notify);
            m_zego_screencapture_capture_dwm_composition_change_notify = new ScreenCaptureManager.zego_screencapture_capture_dwm_composition_change_notify_func(zego_screencapture_capture_dwm_composition_change_notify);
            m_zego_screencapture_captured_frame_available_notify = new ScreenCaptureManager.zego_screencapture_captured_frame_available_notify_func(zego_screencapture_captured_frame_available_notify);

            string str = System.Windows.Forms.Application.StartupPath;
            ScreenCaptureManager.zego_screencapture_set_log_level(ZegoScreenCaptureLogLevel.kZegoLogLevelDebug, str);

            //这里必须注册函数对象，不能直接传入函数名
            ScreenCaptureManager.zego_screencapture_reg_capture_error_notify(m_zego_screencapture_capture_error_notify, IntPtr.Zero);
            ScreenCaptureManager.zego_screencapture_reg_capture_process_window_change_notify(m_zego_screencapture_capture_process_window_change_notify, IntPtr.Zero);
            ScreenCaptureManager.zego_screencapture_reg_mutiple_captured_frame_available_notify(m_zego_screencapture_mutiple_captured_frame_available_notify, IntPtr.Zero);
            ScreenCaptureManager.zego_screencapture_reg_capture_dwm_composition_change_notify(m_zego_screencapture_capture_dwm_composition_change_notify, IntPtr.Zero);
            ScreenCaptureManager.zego_screencapture_reg_captured_window_status_change_notify(m_zego_screencapture_captured_window_status_change_notify, IntPtr.Zero);
            ScreenCaptureManager.zego_screencapture_reg_captured_frame_available_notify(m_zego_screencapture_captured_frame_available_notify, IntPtr.Zero);

            ScreenCaptureManager.zego_screencapture_init();
            ScreenCaptureManager.zego_screencapture_set_capture_video_pixel_format(ZegoScreenCaptureVideoPixelFormat.kZegoPixelFormatBGRA32);
        }

        private void UninitScreenCapture()
        {
            //ScreenCaptureManager.zego_screencapture_reg_captured_frame_available_notify(IntPtr.Zero, IntPtr.Zero);
            ScreenCaptureManager.zego_screencapture_uninit();
        }

            private void InitUI()
        {
            //初始化窗口列表
            buttonRefreshWindow_Click(null, null);
            //初始化屏幕列表
            buttonRefreshScreen_Click(null, null);

            m_resolutions.Add(new Tuple<int, int>(640, 360));
            m_resolutions.Add(new Tuple<int, int>(854, 480));
            m_resolutions.Add(new Tuple<int, int>(1280, 720));
            m_resolutions.Add(new Tuple<int, int>(1920, 1080));
            m_resolutions.Add(new Tuple<int, int>(720, 1280));

            foreach (var item in m_resolutions)
            {
                string str = string.Format("{0:D}*{1:D}", item.Item1, item.Item2);
                this.comboBoxResolution.Items.Add(str);
            }

            this.comboBoxResolution.SelectedIndex = 0;

            this.trackBarBitrate.Minimum = 300;
            this.trackBarBitrate.Maximum = 3000;
            this.labelBitrate.Text = this.trackBarBitrate.Value.ToString() + "K";

            this.trackBarFPS.Minimum = 1;
            this.trackBarFPS.Maximum = 60;
            this.trackBarFPS.Value = 15;
            this.labelFPS.Text = this.trackBarFPS.Value.ToString();

            this.checkBoxCursor.Checked = true;
            this.checkBoxClickanimation.Checked = true;

            //初始化屏幕区域
            int left = 0;
            int top = 0;
            int width = 0;
            int height = 0;
            ScreenCaptureManager.zego_screencapture_get_virtual_desktop_rect(ref left, ref top, ref width, ref height);
            this.trackBarX.Minimum = 0;
            this.trackBarX.Maximum = width - 1;
            this.trackBarX.Value = 0;
            this.labelX.Text = "X: " + this.trackBarX.Value.ToString();

            this.trackBarY.Minimum = 0;
            this.trackBarY.Maximum = height - 1;
            this.trackBarY.Value = 0;
            this.labelY.Text = "Y: " + this.trackBarY.Value.ToString();

            this.trackBarW.Minimum = 0;
            this.trackBarW.Maximum = width;
            this.trackBarW.Value = width;
            this.labelW.Text = "W: " + this.trackBarW.Value.ToString();

            this.trackBarH.Minimum = 0;
            this.trackBarH.Maximum = height;
            this.trackBarH.Value = height;
            this.labelH.Text = "H: " + this.trackBarH.Value.ToString();
        }

        public void zego_on_engine_uninit(zego_engine_state state, IntPtr user_context)
        {

        }

        public void zego_on_publisher_state_update(string stream_id, zego_publisher_state state, int error_code, string extend_data, IntPtr user_context)
        {
            string strMsg = string.Format("## 流状态变更 > {0:D} ##", state);
            showMsg(strMsg);

            if (extend_data != null && extend_data != "{}")
            {
                string strRtmpUrl = "rtmp_url_list";
                string strHlsUrl = "hls_url_list";

                //rtmp
                int iPos1 = extend_data.IndexOf(strRtmpUrl);
                int iPos2 = extend_data.IndexOf("[", iPos1 + 1);
                int iPos3 = extend_data.IndexOf("]", iPos2 + 1);
                if (iPos3 - iPos2 - 3 > 0)
                {
                    strRtmpUrl = extend_data.Substring(iPos2 + 2, iPos3 - iPos2 - 3);
                }

                //hls
                iPos1 = extend_data.IndexOf(strHlsUrl, iPos3);
                iPos2 = extend_data.IndexOf("[", iPos3 + 1);
                iPos3 = extend_data.IndexOf("]", iPos2 + 1);
                if (iPos3 - iPos2 - 3 > 0)
                {
                    strHlsUrl = extend_data.Substring(iPos2 + 2, iPos3 - iPos2 - 3);
                }

                DoInMainThread(() =>
                {
                    this.textBoxRtmpUrl.Text = strRtmpUrl;
                    this.textBoxHlsUrl.Text = strHlsUrl;
                });
            }
        }

        public void zego_on_publisher_quality_update(string stream_id, zego_publish_stream_quality quality, IntPtr user_context)
        {
            // 推流质量实时统计
            string strMsg = string.Format("#### 实时统计 [{0:S}] 质量: {1:D} 帧率: {2:F} 码率: {3:F} ####", stream_id, quality.level, quality.video_send_fps, quality.video_kbps);
            showMsg(strMsg);
        }

        public void zego_on_engine_state_update(zego_engine_state state, IntPtr user_context)
        {
            if (state == zego_engine_state.zego_engine_state_start)
            {
                showMsg("engine_state_start");
            }
            else
            {
                showMsg("engine_state_stop");
            }
        }

        public void zego_on_room_state_update(string room_id, zego_room_state state, int error_code, string extended_data, IntPtr user_context)
        {
            if (state == zego_room_state.zego_room_state_connected)
            {
                showMsg("登录成功");
            }
        }

        public void zego_screencapture_capture_error_notify(ZegoScreenCaptureCaptureError error, IntPtr user_data)
        {
            //             DoInMainThread(() =>
            //             {
            //                 showMsg("出错");
            //             });
        }

        public void zego_screencapture_captured_frame_available_notify(IntPtr data, uint length, IntPtr video_frame_format, UInt64 reference_time, uint reference_time_scale, IntPtr user_data)
        {
            //本地渲染采集的数据
            ZegoScreenCaptureVideoCaptureFormat format = (ZegoScreenCaptureVideoCaptureFormat)Marshal.PtrToStructure(video_frame_format, typeof(ZegoScreenCaptureVideoCaptureFormat));
            Bitmap bmp = new Bitmap(format.width, format.height, PixelFormat.Format32bppArgb);

            // Lock the bitmap's bits.  
            Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            System.Drawing.Imaging.BitmapData bmpData = bmp.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, bmp.PixelFormat);

            // Get the address of the first line.
            IntPtr ptr = bmpData.Scan0;

            byte[] rgbValues = new byte[(int)length];

            Marshal.Copy(data, rgbValues, 0, (int)length);

            // Copy the RGB values back to the bitmap
            Marshal.Copy(rgbValues, 0, ptr, (int)length);

            // Unlock the bits.
            bmp.UnlockBits(bmpData);

            this.DoInMainThread(() =>
            {
                if (m_screenCaptureView != null)
                    m_screenCaptureView.setBitmap(bmp);
            });

            //推流
            zego_video_frame_param param = new zego_video_frame_param();
            param.strides = new int[4];
            param.width = format.width;
            param.height = format.height;
            if (format.video_pixel_format == ZegoScreenCaptureVideoPixelFormat.kZegoPixelFormatI420)
            {
                param.strides[0] = format.strides[0];
                param.strides[1] = format.strides[1];
                param.strides[2] = format.strides[2];
            }
            else
            {
                param.strides[0] = format.strides[0];
            }

            param.format = (zego_video_frame_format)format.video_pixel_format;
            param.rotation = format.rotation;
            ExpressManager.zego_express_send_custom_video_capture_raw_data(data, length, param, reference_time, reference_time_scale, zego_publish_channel.zego_publish_channel_main);
        }

        public void zego_screencapture_mutiple_captured_frame_available_notify(IntPtr data, uint length, IntPtr video_frame_format, UInt64 reference_time, uint reference_time_scale, uint handle, IntPtr user_data)
        {

        }

        public void zego_screencapture_capture_dwm_composition_change_notify(bool enable, IntPtr data)
        {

        }

        public void zego_screencapture_capture_process_window_change_notify(int status, ZegoScreenCaptureProcessWindow window_info, IntPtr user_data)
        {

        }

        public void zego_screencapture_captured_window_status_change_notify(int status_code, uint handle, ZegoScreenCaptureRect rect, IntPtr user_data)
        {

        }

        private void richTextBoxMsg_TextChanged(object sender, EventArgs e)
        {

        }

        private void buttonAddExcludeWindow_Click(object sender, EventArgs e)
        {
            //添加采集过滤窗口
            IntPtr[] handle_list = new IntPtr[1];
            handle_list[0] = m_windows2[this.comboBoxWindow2.SelectedIndex];
            ScreenCaptureManager.zego_screencapture_set_excluded_windows(handle_list, 1, true);
        }

        private void radioButtonScreen_CheckedChanged(object sender, EventArgs e)
        {
            //设置屏幕采集
            ScreenCaptureManager.zego_screencapture_set_target_screen(this.comboBoxScreen.Text);
        }

        private void radioButtonWindow_CheckedChanged(object sender, EventArgs e)
        {
            //设置窗口采集
            ScreenCaptureManager.zego_screencapture_set_target_window(m_windows[this.comboBoxWindow.SelectedIndex]);
        }

        private void radioButtonRect_CheckedChanged(object sender, EventArgs e)
        {
            //设置区域采集
            ScreenCaptureManager.zego_screencapture_set_target_rect("", this.trackBarX.Value, this.trackBarY.Value, this.trackBarW.Value, this.trackBarH.Value);
        }

        private void buttonRemoveExcludeWindow_Click(object sender, EventArgs e)
        {
            //移除采集过滤窗口
            IntPtr[] handle_list = new IntPtr[1];
            handle_list[0] = m_windows2[this.comboBoxWindow2.SelectedIndex];
            ScreenCaptureManager.zego_screencapture_set_excluded_windows(handle_list, 1, false);
        }

        private void buttonAddCaptureWindow_Click(object sender, EventArgs e)
        {
            //添加多目标采集
            IntPtr[] handle_list = new IntPtr[1];
            handle_list[0] = m_windows2[this.comboBoxWindow2.SelectedIndex];
            ScreenCaptureManager.zego_screencapture_set_extra_target_windows(handle_list, 1, true);
        }

        private void buttonRemoveCaptureWindow_Click(object sender, EventArgs e)
        {
            //移除多目标采集
            IntPtr[] handle_list = new IntPtr[1];
            handle_list[0] = m_windows2[this.comboBoxWindow2.SelectedIndex];
            ScreenCaptureManager.zego_screencapture_set_extra_target_windows(handle_list, 1, false);
        }

        private void buttonThumbnail_Click(object sender, EventArgs e)
        {

        }

        private void buttonView_Click(object sender, EventArgs e)
        {
            m_screenCaptureView.Show();
        }

        private void buttonCapture_Click(object sender, EventArgs e)
        {
            int startCapture = ScreenCaptureManager.zego_screencapture_is_capturing();

            if (startCapture == 0)
            {
                ScreenCaptureManager.zego_screencapture_start_capture();
                this.buttonCapture.Text = "停止采集";
            }
            else
            {
                ScreenCaptureManager.zego_screencapture_stop_capture();
                this.buttonCapture.Text = "开始采集";
            }
        }

        private void buttonRefreshWindow_Click(object sender, EventArgs e)
        {
            //获取窗口列表
            m_windows.Clear();
            m_windows2.Clear();
            this.comboBoxWindow.Items.Clear();
            this.comboBoxWindow2.Items.Clear();
            uint count = 0;
            IntPtr windowsPtr = ScreenCaptureManager.zego_screencapture_enum_window_list(1, ref count);
            if (count > 0)
            {
                for (int i = 0; i < count; i++)
                {
                    var Ptr = windowsPtr + Marshal.SizeOf<ZegoScreenCaptureWindowItem>() * i;
                    var window = (ZegoScreenCaptureWindowItem)Marshal.PtrToStructure(Ptr, typeof(ZegoScreenCaptureWindowItem));

                    this.comboBoxWindow.Items.Add(Encoding.UTF8.GetString(Encoding.Default.GetBytes(window.title)));
                    this.comboBoxWindow2.Items.Add(Encoding.UTF8.GetString(Encoding.Default.GetBytes(window.title)));

                    m_windows.Add(window.handle);
                    m_windows2.Add(window.handle);
                }
            }
            this.comboBoxWindow.SelectedIndex = 0;
            this.comboBoxWindow2.SelectedIndex = 0;
            ScreenCaptureManager.zego_screencapture_free_window_list(windowsPtr);
        }

        private void buttonPublish_Click(object sender, EventArgs e)
        {
            ExpressManager.zego_express_start_publishing_stream(m_userID, zego_publish_channel.zego_publish_channel_main);
        }

        private void trackBarBitrate_Scroll(object sender, EventArgs e)
        {
            this.labelBitrate.Text = this.trackBarBitrate.Value.ToString() + "K";

            SetVideoConfig();
        }

        private void trackBarFPS_Scroll(object sender, EventArgs e)
        {
            this.labelFPS.Text = this.trackBarFPS.Value.ToString();

            SetVideoConfig();
        }

        private void trackBarX_Scroll(object sender, EventArgs e)
        {
            this.labelX.Text = "X: " + this.trackBarX.Value.ToString();
            targetRectChange();
        }

        private void trackBarY_Scroll(object sender, EventArgs e)
        {
            this.labelY.Text = "Y: " + this.trackBarY.Value.ToString();
            targetRectChange();
        }

        private void trackBarH_Scroll(object sender, EventArgs e)
        {
            this.labelH.Text = "H: " + this.trackBarH.Value.ToString();
            targetRectChange();
        }

        private void trackBarW_Scroll(object sender, EventArgs e)
        {
            this.labelW.Text = "W: " + this.trackBarW.Value.ToString();
            targetRectChange();
        }

        private void checkBoxCursor_CheckedChanged(object sender, EventArgs e)
        {
            //设置是否显示鼠标
            ScreenCaptureManager.zego_screencapture_set_cursor_visible(this.checkBoxCursor.Checked ? 1 : 0);
        }

        private void checkBoxClickanimation_CheckedChanged(object sender, EventArgs e)
        {
            //设置是否显示鼠标点击动画
            ScreenCaptureManager.zego_screencapture_enable_click_animation(this.checkBoxClickanimation.Checked ? 1 : 0);
        }

        private void comboBoxWindow_SelectedIndexChanged(object sender, EventArgs e)
        {
            //窗口采集时切换采集窗口
            if (this.radioButtonWindow.Checked)
            {
                ScreenCaptureManager.zego_screencapture_set_target_window(m_windows[this.comboBoxWindow.SelectedIndex]);
                ZegoScreenCaptureRect rect = new ZegoScreenCaptureRect();
                ScreenCaptureManager.zego_screencapture_get_window_rect(m_windows[this.comboBoxWindow.SelectedIndex], ref rect);
            }
        }

        private void comboBoxScreen_SelectedIndexChanged(object sender, EventArgs e)
        {
            //屏幕采集时切换采集屏幕
            if (this.radioButtonScreen.Checked)
            {
                ScreenCaptureManager.zego_screencapture_set_target_screen(this.comboBoxScreen.Text);
            }
        }

        private void comboBoxResolution_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetVideoConfig();
        }

        private void buttonRefreshScreen_Click(object sender, EventArgs e)
        {
            this.comboBoxScreen.Items.Clear();
            //初始化屏幕列表
            uint count = 0;
            IntPtr screenPtr = ScreenCaptureManager.zego_screencapture_enum_screen_list(ref count);
            if (count > 0)
            {
                ZegoScreenCaptureScreenItem[] screens = new ZegoScreenCaptureScreenItem[count];

                for (int i = 0; i < count; i++)
                {
                    var Ptr = screenPtr + Marshal.SizeOf<ZegoScreenCaptureScreenItem>() * i;
                    screens[i] = (ZegoScreenCaptureScreenItem)Marshal.PtrToStructure(Ptr, typeof(ZegoScreenCaptureScreenItem));

                    this.comboBoxScreen.Items.Add(Encoding.UTF8.GetString(Encoding.Default.GetBytes(screens[i].ZegoScreenName)));

                }
                this.comboBoxScreen.SelectedIndex = 0;
                ScreenCaptureManager.zego_screencapture_free_screen_list(screenPtr);
            }
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void targetRectChange()
        {
            //设置区域采集
            if (this.radioButtonRect.Checked)
            {
                ScreenCaptureManager.zego_screencapture_set_target_rect("", this.trackBarX.Value, this.trackBarY.Value, this.trackBarW.Value, this.trackBarH.Value);
            }
        }

        private void SetVideoConfig()
        {
            this.labelFPS.Text = this.trackBarFPS.Value.ToString();
            ScreenCaptureManager.zego_screencapture_set_fps(this.trackBarFPS.Value);

            zego_video_config config = ExpressManager.zego_express_get_video_config(zego_publish_channel.zego_publish_channel_main);
            config.fps = this.trackBarFPS.Value;
            config.bitrate = this.trackBarBitrate.Value;
            config.encode_width = this.m_resolutions[this.comboBoxResolution.SelectedIndex].Item1;
            config.encode_height = this.m_resolutions[this.comboBoxResolution.SelectedIndex].Item2;
            ExpressManager.zego_express_set_video_config(config, zego_publish_channel.zego_publish_channel_main);
        }

        private void showMsg(string msg)
        {
            DoInMainThread(() =>
            {
                this.richTextBoxMsg.Select(this.richTextBoxMsg.TextLength, 0);
                this.richTextBoxMsg.ScrollToCaret();
                this.richTextBoxMsg.AppendText(msg + "\n");
            });
        }

        private delegate void DoInMainThreadDelegate();

        private void DoInMainThread(DoInMainThreadDelegate func)
        {
            this.Invoke(func);
        }

        private void Form_Closed(object sender, FormClosedEventArgs e)
        {
            ScreenCaptureManager.zego_screencapture_stop_capture();
        }

        private void Form_Closing(object sender, FormClosingEventArgs e)
        {
            ScreenCaptureManager.zego_screencapture_stop_capture();
        }
    }
}

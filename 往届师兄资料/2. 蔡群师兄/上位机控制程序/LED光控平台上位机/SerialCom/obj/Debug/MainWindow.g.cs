﻿#pragma checksum "..\..\MainWindow.xaml" "{8829d00f-11b8-4213-878b-770e8597ac16}" "16C31CB92F6B3EDCF91A58FD58419D5D0EB8BDD5AE39DDDD9D9499E0F424458E"
//------------------------------------------------------------------------------
// <auto-generated>
//     此代码由工具生成。
//     运行时版本:4.0.30319.42000
//
//     对此文件的更改可能会导致不正确的行为，并且如果
//     重新生成代码，这些更改将会丢失。
// </auto-generated>
//------------------------------------------------------------------------------

using SerialCom;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace SerialCom {
    
    
    /// <summary>
    /// MainWindow
    /// </summary>
    public partial class MainWindow : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 106 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock Port;
        
        #line default
        #line hidden
        
        
        #line 107 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock BaundRate;
        
        #line default
        #line hidden
        
        
        #line 108 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock Parity;
        
        #line default
        #line hidden
        
        
        #line 109 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock DataBits;
        
        #line default
        #line hidden
        
        
        #line 110 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock StopBits;
        
        #line default
        #line hidden
        
        
        #line 111 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox AvailableComCbobox;
        
        #line default
        #line hidden
        
        
        #line 112 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox RateListCbobox;
        
        #line default
        #line hidden
        
        
        #line 113 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox ParityComCbobox;
        
        #line default
        #line hidden
        
        
        #line 114 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox DataBitsCbobox;
        
        #line default
        #line hidden
        
        
        #line 115 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox StopBitsCbobox;
        
        #line default
        #line hidden
        
        
        #line 116 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button defaultSet;
        
        #line default
        #line hidden
        
        
        #line 117 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button openBtn;
        
        #line default
        #line hidden
        
        
        #line 118 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Image OpenImage;
        
        #line default
        #line hidden
        
        
        #line 125 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.CheckBox recModeCheck;
        
        #line default
        #line hidden
        
        
        #line 126 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button saveBtn;
        
        #line default
        #line hidden
        
        
        #line 140 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label recPrompt;
        
        #line default
        #line hidden
        
        
        #line 141 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button stopRecBtn;
        
        #line default
        #line hidden
        
        
        #line 142 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button recClearBtn;
        
        #line default
        #line hidden
        
        
        #line 143 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Border recBorder;
        
        #line default
        #line hidden
        
        
        #line 144 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ScrollViewer recScrol;
        
        #line default
        #line hidden
        
        
        #line 146 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox recTBox;
        
        #line default
        #line hidden
        
        
        #line 149 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button;
        
        #line default
        #line hidden
        
        
        #line 150 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button1;
        
        #line default
        #line hidden
        
        
        #line 151 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button2;
        
        #line default
        #line hidden
        
        
        #line 152 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button3;
        
        #line default
        #line hidden
        
        
        #line 153 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button4;
        
        #line default
        #line hidden
        
        
        #line 154 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button5;
        
        #line default
        #line hidden
        
        
        #line 155 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button6;
        
        #line default
        #line hidden
        
        
        #line 156 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label label;
        
        #line default
        #line hidden
        
        
        #line 157 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label label1;
        
        #line default
        #line hidden
        
        
        #line 158 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button7;
        
        #line default
        #line hidden
        
        
        #line 159 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button8;
        
        #line default
        #line hidden
        
        
        #line 160 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button9;
        
        #line default
        #line hidden
        
        
        #line 161 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button10;
        
        #line default
        #line hidden
        
        
        #line 162 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button11;
        
        #line default
        #line hidden
        
        
        #line 163 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button12;
        
        #line default
        #line hidden
        
        
        #line 164 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button13;
        
        #line default
        #line hidden
        
        
        #line 165 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button14;
        
        #line default
        #line hidden
        
        
        #line 166 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button15;
        
        #line default
        #line hidden
        
        
        #line 167 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button16;
        
        #line default
        #line hidden
        
        
        #line 168 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button17;
        
        #line default
        #line hidden
        
        
        #line 169 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button19;
        
        #line default
        #line hidden
        
        
        #line 170 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label label_Copy1;
        
        #line default
        #line hidden
        
        
        #line 188 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ScrollViewer sendScrol;
        
        #line default
        #line hidden
        
        
        #line 189 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox sendTBox;
        
        #line default
        #line hidden
        
        
        #line 202 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.CheckBox sendModeCheck;
        
        #line default
        #line hidden
        
        
        #line 203 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.CheckBox autoSendCheck;
        
        #line default
        #line hidden
        
        
        #line 204 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock Cycle;
        
        #line default
        #line hidden
        
        
        #line 205 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox Time;
        
        #line default
        #line hidden
        
        
        #line 206 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock Unit;
        
        #line default
        #line hidden
        
        
        #line 207 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button openFileBtn;
        
        #line default
        #line hidden
        
        
        #line 208 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button sendClearBtn;
        
        #line default
        #line hidden
        
        
        #line 209 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button countClearBtn;
        
        #line default
        #line hidden
        
        
        #line 210 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button sendBtn;
        
        #line default
        #line hidden
        
        
        #line 216 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock sendCount;
        
        #line default
        #line hidden
        
        
        #line 218 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock recCount;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/SerialCom;component/mainwindow.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\MainWindow.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            
            #line 6 "..\..\MainWindow.xaml"
            ((SerialCom.MainWindow)(target)).Closed += new System.EventHandler(this.Window_Closed);
            
            #line default
            #line hidden
            
            #line 6 "..\..\MainWindow.xaml"
            ((SerialCom.MainWindow)(target)).Closing += new System.ComponentModel.CancelEventHandler(this.Window_Closing);
            
            #line default
            #line hidden
            
            #line 6 "..\..\MainWindow.xaml"
            ((SerialCom.MainWindow)(target)).Loaded += new System.Windows.RoutedEventHandler(this.Window_Loaded);
            
            #line default
            #line hidden
            return;
            case 2:
            
            #line 9 "..\..\MainWindow.xaml"
            ((System.Windows.Input.CommandBinding)(target)).Executed += new System.Windows.Input.ExecutedRoutedEventHandler(this.FileOpen);
            
            #line default
            #line hidden
            return;
            case 3:
            
            #line 11 "..\..\MainWindow.xaml"
            ((System.Windows.Input.CommandBinding)(target)).Executed += new System.Windows.Input.ExecutedRoutedEventHandler(this.FileSave);
            
            #line default
            #line hidden
            return;
            case 4:
            
            #line 13 "..\..\MainWindow.xaml"
            ((System.Windows.Input.CommandBinding)(target)).Executed += new System.Windows.Input.ExecutedRoutedEventHandler(this.Window_Closed);
            
            #line default
            #line hidden
            return;
            case 5:
            
            #line 48 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.SaveNew_Click);
            
            #line default
            #line hidden
            return;
            case 6:
            
            #line 49 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.SaveOld_Click);
            
            #line default
            #line hidden
            return;
            case 7:
            
            #line 58 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.MenuItem_Click);
            
            #line default
            #line hidden
            return;
            case 8:
            
            #line 62 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.info_click);
            
            #line default
            #line hidden
            return;
            case 9:
            
            #line 67 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.feedBack_Click);
            
            #line default
            #line hidden
            return;
            case 10:
            
            #line 72 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.shiyong_Click);
            
            #line default
            #line hidden
            return;
            case 11:
            this.Port = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 12:
            this.BaundRate = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 13:
            this.Parity = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 14:
            this.DataBits = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 15:
            this.StopBits = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 16:
            this.AvailableComCbobox = ((System.Windows.Controls.ComboBox)(target));
            
            #line 111 "..\..\MainWindow.xaml"
            this.AvailableComCbobox.PreviewMouseDown += new System.Windows.Input.MouseButtonEventHandler(this.AvailableComCbobox_PreviewMouseDown);
            
            #line default
            #line hidden
            return;
            case 17:
            this.RateListCbobox = ((System.Windows.Controls.ComboBox)(target));
            
            #line 112 "..\..\MainWindow.xaml"
            this.RateListCbobox.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.RateListCbobox_SelectionChanged);
            
            #line default
            #line hidden
            return;
            case 18:
            this.ParityComCbobox = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 19:
            this.DataBitsCbobox = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 20:
            this.StopBitsCbobox = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 21:
            this.defaultSet = ((System.Windows.Controls.Button)(target));
            
            #line 116 "..\..\MainWindow.xaml"
            this.defaultSet.Click += new System.Windows.RoutedEventHandler(this.defaultSet_Click);
            
            #line default
            #line hidden
            return;
            case 22:
            this.openBtn = ((System.Windows.Controls.Button)(target));
            
            #line 117 "..\..\MainWindow.xaml"
            this.openBtn.Click += new System.Windows.RoutedEventHandler(this.Button_Open);
            
            #line default
            #line hidden
            return;
            case 23:
            this.OpenImage = ((System.Windows.Controls.Image)(target));
            return;
            case 24:
            this.recModeCheck = ((System.Windows.Controls.CheckBox)(target));
            return;
            case 25:
            this.saveBtn = ((System.Windows.Controls.Button)(target));
            return;
            case 26:
            this.recPrompt = ((System.Windows.Controls.Label)(target));
            return;
            case 27:
            this.stopRecBtn = ((System.Windows.Controls.Button)(target));
            
            #line 141 "..\..\MainWindow.xaml"
            this.stopRecBtn.Click += new System.Windows.RoutedEventHandler(this.stopRecBtn_Click);
            
            #line default
            #line hidden
            return;
            case 28:
            this.recClearBtn = ((System.Windows.Controls.Button)(target));
            
            #line 142 "..\..\MainWindow.xaml"
            this.recClearBtn.Click += new System.Windows.RoutedEventHandler(this.recClearBtn_Click);
            
            #line default
            #line hidden
            return;
            case 29:
            this.recBorder = ((System.Windows.Controls.Border)(target));
            return;
            case 30:
            this.recScrol = ((System.Windows.Controls.ScrollViewer)(target));
            return;
            case 31:
            this.recTBox = ((System.Windows.Controls.TextBox)(target));
            
            #line 146 "..\..\MainWindow.xaml"
            this.recTBox.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.recTBox_TextChanged);
            
            #line default
            #line hidden
            return;
            case 32:
            this.button = ((System.Windows.Controls.Button)(target));
            
            #line 149 "..\..\MainWindow.xaml"
            this.button.Click += new System.Windows.RoutedEventHandler(this.button_Click_1);
            
            #line default
            #line hidden
            return;
            case 33:
            this.button1 = ((System.Windows.Controls.Button)(target));
            
            #line 150 "..\..\MainWindow.xaml"
            this.button1.Click += new System.Windows.RoutedEventHandler(this.button1_Click);
            
            #line default
            #line hidden
            return;
            case 34:
            this.button2 = ((System.Windows.Controls.Button)(target));
            
            #line 151 "..\..\MainWindow.xaml"
            this.button2.Click += new System.Windows.RoutedEventHandler(this.button2_Click);
            
            #line default
            #line hidden
            return;
            case 35:
            this.button3 = ((System.Windows.Controls.Button)(target));
            
            #line 152 "..\..\MainWindow.xaml"
            this.button3.Click += new System.Windows.RoutedEventHandler(this.button3_Click);
            
            #line default
            #line hidden
            return;
            case 36:
            this.button4 = ((System.Windows.Controls.Button)(target));
            
            #line 153 "..\..\MainWindow.xaml"
            this.button4.Click += new System.Windows.RoutedEventHandler(this.button4_Click);
            
            #line default
            #line hidden
            return;
            case 37:
            this.button5 = ((System.Windows.Controls.Button)(target));
            
            #line 154 "..\..\MainWindow.xaml"
            this.button5.Click += new System.Windows.RoutedEventHandler(this.button5_Click);
            
            #line default
            #line hidden
            return;
            case 38:
            this.button6 = ((System.Windows.Controls.Button)(target));
            
            #line 155 "..\..\MainWindow.xaml"
            this.button6.Click += new System.Windows.RoutedEventHandler(this.button6_Click);
            
            #line default
            #line hidden
            return;
            case 39:
            this.label = ((System.Windows.Controls.Label)(target));
            return;
            case 40:
            this.label1 = ((System.Windows.Controls.Label)(target));
            return;
            case 41:
            this.button7 = ((System.Windows.Controls.Button)(target));
            
            #line 158 "..\..\MainWindow.xaml"
            this.button7.Click += new System.Windows.RoutedEventHandler(this.button7_Click);
            
            #line default
            #line hidden
            return;
            case 42:
            this.button8 = ((System.Windows.Controls.Button)(target));
            
            #line 159 "..\..\MainWindow.xaml"
            this.button8.Click += new System.Windows.RoutedEventHandler(this.button8_Click);
            
            #line default
            #line hidden
            return;
            case 43:
            this.button9 = ((System.Windows.Controls.Button)(target));
            
            #line 160 "..\..\MainWindow.xaml"
            this.button9.Click += new System.Windows.RoutedEventHandler(this.button9_Click);
            
            #line default
            #line hidden
            return;
            case 44:
            this.button10 = ((System.Windows.Controls.Button)(target));
            
            #line 161 "..\..\MainWindow.xaml"
            this.button10.Click += new System.Windows.RoutedEventHandler(this.button10_Click);
            
            #line default
            #line hidden
            return;
            case 45:
            this.button11 = ((System.Windows.Controls.Button)(target));
            
            #line 162 "..\..\MainWindow.xaml"
            this.button11.Click += new System.Windows.RoutedEventHandler(this.button11_Click);
            
            #line default
            #line hidden
            return;
            case 46:
            this.button12 = ((System.Windows.Controls.Button)(target));
            
            #line 163 "..\..\MainWindow.xaml"
            this.button12.Click += new System.Windows.RoutedEventHandler(this.button12_Click);
            
            #line default
            #line hidden
            return;
            case 47:
            this.button13 = ((System.Windows.Controls.Button)(target));
            
            #line 164 "..\..\MainWindow.xaml"
            this.button13.Click += new System.Windows.RoutedEventHandler(this.button13_Click);
            
            #line default
            #line hidden
            return;
            case 48:
            this.button14 = ((System.Windows.Controls.Button)(target));
            
            #line 165 "..\..\MainWindow.xaml"
            this.button14.Click += new System.Windows.RoutedEventHandler(this.button14_Click);
            
            #line default
            #line hidden
            return;
            case 49:
            this.button15 = ((System.Windows.Controls.Button)(target));
            
            #line 166 "..\..\MainWindow.xaml"
            this.button15.Click += new System.Windows.RoutedEventHandler(this.button15_Click);
            
            #line default
            #line hidden
            return;
            case 50:
            this.button16 = ((System.Windows.Controls.Button)(target));
            
            #line 167 "..\..\MainWindow.xaml"
            this.button16.Click += new System.Windows.RoutedEventHandler(this.button16_Click);
            
            #line default
            #line hidden
            return;
            case 51:
            this.button17 = ((System.Windows.Controls.Button)(target));
            
            #line 168 "..\..\MainWindow.xaml"
            this.button17.Click += new System.Windows.RoutedEventHandler(this.button17_Click);
            
            #line default
            #line hidden
            return;
            case 52:
            this.button19 = ((System.Windows.Controls.Button)(target));
            
            #line 169 "..\..\MainWindow.xaml"
            this.button19.Click += new System.Windows.RoutedEventHandler(this.button19_Click);
            
            #line default
            #line hidden
            return;
            case 53:
            this.label_Copy1 = ((System.Windows.Controls.Label)(target));
            return;
            case 54:
            this.sendScrol = ((System.Windows.Controls.ScrollViewer)(target));
            return;
            case 55:
            this.sendTBox = ((System.Windows.Controls.TextBox)(target));
            return;
            case 56:
            this.sendModeCheck = ((System.Windows.Controls.CheckBox)(target));
            
            #line 202 "..\..\MainWindow.xaml"
            this.sendModeCheck.Checked += new System.Windows.RoutedEventHandler(this.sendModeCheck_Checked);
            
            #line default
            #line hidden
            return;
            case 57:
            this.autoSendCheck = ((System.Windows.Controls.CheckBox)(target));
            
            #line 203 "..\..\MainWindow.xaml"
            this.autoSendCheck.Click += new System.Windows.RoutedEventHandler(this.autoSendCheck_Click);
            
            #line default
            #line hidden
            return;
            case 58:
            this.Cycle = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 59:
            this.Time = ((System.Windows.Controls.TextBox)(target));
            
            #line 205 "..\..\MainWindow.xaml"
            this.Time.KeyDown += new System.Windows.Input.KeyEventHandler(this.Time_KeyDown);
            
            #line default
            #line hidden
            
            #line 205 "..\..\MainWindow.xaml"
            this.Time.LostFocus += new System.Windows.RoutedEventHandler(this.Time_LostFocus);
            
            #line default
            #line hidden
            
            #line 205 "..\..\MainWindow.xaml"
            this.Time.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.Time_TextChanged);
            
            #line default
            #line hidden
            return;
            case 60:
            this.Unit = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 61:
            this.openFileBtn = ((System.Windows.Controls.Button)(target));
            return;
            case 62:
            this.sendClearBtn = ((System.Windows.Controls.Button)(target));
            
            #line 208 "..\..\MainWindow.xaml"
            this.sendClearBtn.Click += new System.Windows.RoutedEventHandler(this.sendClearBtn_Click);
            
            #line default
            #line hidden
            return;
            case 63:
            this.countClearBtn = ((System.Windows.Controls.Button)(target));
            
            #line 209 "..\..\MainWindow.xaml"
            this.countClearBtn.Click += new System.Windows.RoutedEventHandler(this.countClearBtn_Click);
            
            #line default
            #line hidden
            return;
            case 64:
            this.sendBtn = ((System.Windows.Controls.Button)(target));
            
            #line 210 "..\..\MainWindow.xaml"
            this.sendBtn.Click += new System.Windows.RoutedEventHandler(this.Button_Send);
            
            #line default
            #line hidden
            return;
            case 65:
            this.sendCount = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 66:
            this.recCount = ((System.Windows.Controls.TextBlock)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}


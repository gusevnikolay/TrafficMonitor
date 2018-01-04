<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class App
    Inherits Bwl.Framework.FormAppBase

    'Форма переопределяет dispose для очистки списка компонентов.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Является обязательной для конструктора форм Windows Forms
    Private components As System.ComponentModel.IContainer

    'Примечание: следующая процедура является обязательной для конструктора форм Windows Forms
    'Для ее изменения используйте конструктор форм Windows Form.  
    'Не изменяйте ее в редакторе исходного кода.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.bFirmwareUpload = New System.Windows.Forms.GroupBox()
        Me.uploadProgress = New System.Windows.Forms.ProgressBar()
        Me.bUpload = New System.Windows.Forms.Button()
        Me.bFileSelect = New System.Windows.Forms.Button()
        Me.textHexPath = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.bServerConnect = New System.Windows.Forms.Button()
        Me.textServerPort = New System.Windows.Forms.TextBox()
        Me.textServerIp = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.timer = New System.Windows.Forms.Timer(Me.components)
        Me.textDeviceId = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.bFirmwareUpload.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.SuspendLayout()
        '
        'logWriter
        '
        Me.logWriter.Location = New System.Drawing.Point(2, 180)
        Me.logWriter.Size = New System.Drawing.Size(559, 234)
        '
        'bFirmwareUpload
        '
        Me.bFirmwareUpload.Controls.Add(Me.Label3)
        Me.bFirmwareUpload.Controls.Add(Me.textDeviceId)
        Me.bFirmwareUpload.Controls.Add(Me.uploadProgress)
        Me.bFirmwareUpload.Controls.Add(Me.bUpload)
        Me.bFirmwareUpload.Controls.Add(Me.bFileSelect)
        Me.bFirmwareUpload.Controls.Add(Me.textHexPath)
        Me.bFirmwareUpload.Controls.Add(Me.Label2)
        Me.bFirmwareUpload.Location = New System.Drawing.Point(238, 37)
        Me.bFirmwareUpload.Name = "bFirmwareUpload"
        Me.bFirmwareUpload.Size = New System.Drawing.Size(312, 140)
        Me.bFirmwareUpload.TabIndex = 2
        Me.bFirmwareUpload.TabStop = False
        Me.bFirmwareUpload.Text = "Bootloader"
        '
        'uploadProgress
        '
        Me.uploadProgress.Location = New System.Drawing.Point(9, 99)
        Me.uploadProgress.Name = "uploadProgress"
        Me.uploadProgress.Size = New System.Drawing.Size(297, 23)
        Me.uploadProgress.Step = 1
        Me.uploadProgress.TabIndex = 5
        '
        'bUpload
        '
        Me.bUpload.Location = New System.Drawing.Point(229, 69)
        Me.bUpload.Name = "bUpload"
        Me.bUpload.Size = New System.Drawing.Size(77, 23)
        Me.bUpload.TabIndex = 4
        Me.bUpload.Text = "Upload"
        Me.bUpload.UseVisualStyleBackColor = True
        '
        'bFileSelect
        '
        Me.bFileSelect.Location = New System.Drawing.Point(229, 39)
        Me.bFileSelect.Name = "bFileSelect"
        Me.bFileSelect.Size = New System.Drawing.Size(77, 23)
        Me.bFileSelect.TabIndex = 3
        Me.bFileSelect.Text = "File"
        Me.bFileSelect.UseVisualStyleBackColor = True
        '
        'textHexPath
        '
        Me.textHexPath.Location = New System.Drawing.Point(9, 41)
        Me.textHexPath.Name = "textHexPath"
        Me.textHexPath.Size = New System.Drawing.Size(214, 20)
        Me.textHexPath.TabIndex = 2
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(6, 26)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(53, 13)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "HEX path"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.bServerConnect)
        Me.GroupBox2.Controls.Add(Me.textServerPort)
        Me.GroupBox2.Controls.Add(Me.textServerIp)
        Me.GroupBox2.Controls.Add(Me.Label1)
        Me.GroupBox2.Location = New System.Drawing.Point(12, 37)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(220, 140)
        Me.GroupBox2.TabIndex = 3
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Server connection"
        '
        'bServerConnect
        '
        Me.bServerConnect.Location = New System.Drawing.Point(9, 69)
        Me.bServerConnect.Name = "bServerConnect"
        Me.bServerConnect.Size = New System.Drawing.Size(205, 53)
        Me.bServerConnect.TabIndex = 4
        Me.bServerConnect.Text = "Connect"
        Me.bServerConnect.UseVisualStyleBackColor = True
        '
        'textServerPort
        '
        Me.textServerPort.Location = New System.Drawing.Point(153, 42)
        Me.textServerPort.Name = "textServerPort"
        Me.textServerPort.Size = New System.Drawing.Size(61, 20)
        Me.textServerPort.TabIndex = 3
        Me.textServerPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'textServerIp
        '
        Me.textServerIp.Location = New System.Drawing.Point(9, 42)
        Me.textServerIp.Name = "textServerIp"
        Me.textServerIp.Size = New System.Drawing.Size(138, 20)
        Me.textServerIp.TabIndex = 1
        Me.textServerIp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(6, 26)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(41, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Server "
        '
        'timer
        '
        Me.timer.Interval = 500
        '
        'textDeviceId
        '
        Me.textDeviceId.Location = New System.Drawing.Point(94, 71)
        Me.textDeviceId.Name = "textDeviceId"
        Me.textDeviceId.Size = New System.Drawing.Size(129, 20)
        Me.textDeviceId.TabIndex = 6
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(6, 74)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(58, 13)
        Me.Label3.TabIndex = 7
        Me.Label3.Text = "Device ID:"
        '
        'App
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(562, 415)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.bFirmwareUpload)
        Me.Name = "App"
        Me.Text = "SmartCity.FirmwareUploader"
        Me.Controls.SetChildIndex(Me.logWriter, 0)
        Me.Controls.SetChildIndex(Me.bFirmwareUpload, 0)
        Me.Controls.SetChildIndex(Me.GroupBox2, 0)
        Me.bFirmwareUpload.ResumeLayout(False)
        Me.bFirmwareUpload.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents bFirmwareUpload As GroupBox
    Friend WithEvents uploadProgress As ProgressBar
    Friend WithEvents bUpload As Button
    Friend WithEvents bFileSelect As Button
    Friend WithEvents textHexPath As TextBox
    Friend WithEvents Label2 As Label
    Friend WithEvents GroupBox2 As GroupBox
    Friend WithEvents bServerConnect As Button
    Friend WithEvents textServerPort As TextBox
    Friend WithEvents textServerIp As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents timer As Timer
    Friend WithEvents Label3 As Label
    Friend WithEvents textDeviceId As TextBox
End Class

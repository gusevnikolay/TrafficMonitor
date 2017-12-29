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
        Me.TabControl1 = New System.Windows.Forms.TabControl()
        Me.TabPage1 = New System.Windows.Forms.TabPage()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.bUpdateAccessPointsList = New System.Windows.Forms.Button()
        Me.listAccessPoints = New System.Windows.Forms.ListBox()
        Me.TabPage2 = New System.Windows.Forms.TabPage()
        Me.timer = New System.Windows.Forms.Timer(Me.components)
        Me.TabPage3 = New System.Windows.Forms.TabPage()
        Me.TabControl1.SuspendLayout()
        Me.TabPage1.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'logWriter
        '
        Me.logWriter.Location = New System.Drawing.Point(2, 318)
        Me.logWriter.Size = New System.Drawing.Size(670, 127)
        '
        'TabControl1
        '
        Me.TabControl1.Controls.Add(Me.TabPage1)
        Me.TabControl1.Controls.Add(Me.TabPage2)
        Me.TabControl1.Controls.Add(Me.TabPage3)
        Me.TabControl1.Location = New System.Drawing.Point(2, 27)
        Me.TabControl1.Name = "TabControl1"
        Me.TabControl1.SelectedIndex = 0
        Me.TabControl1.Size = New System.Drawing.Size(670, 288)
        Me.TabControl1.TabIndex = 2
        '
        'TabPage1
        '
        Me.TabPage1.Controls.Add(Me.GroupBox1)
        Me.TabPage1.Location = New System.Drawing.Point(4, 22)
        Me.TabPage1.Name = "TabPage1"
        Me.TabPage1.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage1.Size = New System.Drawing.Size(662, 262)
        Me.TabPage1.TabIndex = 0
        Me.TabPage1.Text = "TCP Clients"
        Me.TabPage1.UseVisualStyleBackColor = True
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.bUpdateAccessPointsList)
        Me.GroupBox1.Controls.Add(Me.listAccessPoints)
        Me.GroupBox1.Location = New System.Drawing.Point(6, 6)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(225, 250)
        Me.GroupBox1.TabIndex = 1
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Access Points"
        '
        'bUpdateAccessPointsList
        '
        Me.bUpdateAccessPointsList.Location = New System.Drawing.Point(7, 221)
        Me.bUpdateAccessPointsList.Name = "bUpdateAccessPointsList"
        Me.bUpdateAccessPointsList.Size = New System.Drawing.Size(212, 23)
        Me.bUpdateAccessPointsList.TabIndex = 1
        Me.bUpdateAccessPointsList.Text = "Update"
        Me.bUpdateAccessPointsList.UseVisualStyleBackColor = True
        '
        'listAccessPoints
        '
        Me.listAccessPoints.FormattingEnabled = True
        Me.listAccessPoints.Location = New System.Drawing.Point(6, 19)
        Me.listAccessPoints.Name = "listAccessPoints"
        Me.listAccessPoints.Size = New System.Drawing.Size(213, 199)
        Me.listAccessPoints.TabIndex = 0
        '
        'TabPage2
        '
        Me.TabPage2.Location = New System.Drawing.Point(4, 22)
        Me.TabPage2.Name = "TabPage2"
        Me.TabPage2.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage2.Size = New System.Drawing.Size(662, 262)
        Me.TabPage2.TabIndex = 1
        Me.TabPage2.Text = "Devices"
        Me.TabPage2.UseVisualStyleBackColor = True
        '
        'timer
        '
        Me.timer.Enabled = True
        Me.timer.Interval = 2000
        '
        'TabPage3
        '
        Me.TabPage3.Location = New System.Drawing.Point(4, 22)
        Me.TabPage3.Name = "TabPage3"
        Me.TabPage3.Size = New System.Drawing.Size(662, 262)
        Me.TabPage3.TabIndex = 2
        Me.TabPage3.Text = "Data base"
        Me.TabPage3.UseVisualStyleBackColor = True
        '
        'App
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(672, 445)
        Me.Controls.Add(Me.TabControl1)
        Me.Name = "App"
        Me.Text = "Smart City Server App"
        Me.Controls.SetChildIndex(Me.logWriter, 0)
        Me.Controls.SetChildIndex(Me.TabControl1, 0)
        Me.TabControl1.ResumeLayout(False)
        Me.TabPage1.ResumeLayout(False)
        Me.GroupBox1.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents TabControl1 As TabControl
    Friend WithEvents TabPage1 As TabPage
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents bUpdateAccessPointsList As Button
    Friend WithEvents listAccessPoints As ListBox
    Friend WithEvents TabPage2 As TabPage
    Friend WithEvents timer As Timer
    Friend WithEvents TabPage3 As TabPage
End Class

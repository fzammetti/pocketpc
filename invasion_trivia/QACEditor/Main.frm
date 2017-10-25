VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form MainForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Invasion: Trivia QAC Editor"
   ClientHeight    =   6240
   ClientLeft      =   150
   ClientTop       =   465
   ClientWidth     =   8235
   Icon            =   "Main.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6240
   ScaleWidth      =   8235
   StartUpPosition =   2  'CenterScreen
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   120
      Top             =   5160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      Filter          =   "All Files (*.*)|*.*|QAC Files (*.qac)|*.qac"
      FilterIndex     =   2
   End
   Begin MSComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   25
      Top             =   5865
      Width           =   8235
      _ExtentX        =   14526
      _ExtentY        =   661
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton ClearFields 
      Caption         =   "Clear Fields"
      Enabled         =   0   'False
      Height          =   495
      Left            =   6600
      TabIndex        =   24
      Top             =   4320
      Width           =   1455
   End
   Begin VB.OptionButton CorrectAnswer4 
      Enabled         =   0   'False
      Height          =   375
      Left            =   3120
      TabIndex        =   22
      Top             =   5280
      Width           =   255
   End
   Begin VB.OptionButton CorrectAnswer3 
      Enabled         =   0   'False
      Height          =   375
      Left            =   3120
      TabIndex        =   21
      Top             =   4560
      Width           =   255
   End
   Begin VB.OptionButton CorrectAnswer2 
      Enabled         =   0   'False
      Height          =   375
      Left            =   3120
      TabIndex        =   20
      Top             =   3840
      Width           =   255
   End
   Begin VB.OptionButton CorrectAnswer1 
      Enabled         =   0   'False
      Height          =   375
      Left            =   3120
      TabIndex        =   19
      Top             =   3120
      Width           =   255
   End
   Begin VB.TextBox Answer4 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   3600
      MaxLength       =   25
      TabIndex        =   18
      Top             =   5280
      Width           =   2655
   End
   Begin VB.TextBox Answer3 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   3600
      MaxLength       =   25
      TabIndex        =   16
      Top             =   4560
      Width           =   2655
   End
   Begin VB.TextBox Answer2 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   3600
      MaxLength       =   25
      TabIndex        =   15
      Top             =   3840
      Width           =   2655
   End
   Begin VB.TextBox Answer1 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   3600
      MaxLength       =   25
      TabIndex        =   14
      Top             =   3120
      Width           =   2655
   End
   Begin VB.CommandButton DeleteQuestion 
      Caption         =   "Delete Question"
      Enabled         =   0   'False
      Height          =   495
      Left            =   6600
      TabIndex        =   10
      Top             =   3720
      Width           =   1455
   End
   Begin VB.CommandButton SaveQuestion 
      Caption         =   "Save Question"
      Enabled         =   0   'False
      Height          =   495
      Left            =   6600
      TabIndex        =   9
      Top             =   3120
      Width           =   1455
   End
   Begin VB.TextBox QuestionLine3 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      MaxLength       =   25
      TabIndex        =   8
      Top             =   4560
      Width           =   2655
   End
   Begin VB.TextBox QuestionLine2 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      MaxLength       =   25
      TabIndex        =   7
      Top             =   3840
      Width           =   2655
   End
   Begin VB.TextBox QuestionLine1 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      MaxLength       =   25
      TabIndex        =   6
      Top             =   3120
      Width           =   2655
   End
   Begin VB.Frame MenuDivider 
      Height          =   28
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   8445
   End
   Begin VB.ListBox QuestionList 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   2010
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   7935
   End
   Begin VB.Label CorrectAnswerLabel 
      Caption         =   "Correct Answer"
      Height          =   375
      Left            =   2880
      TabIndex        =   23
      Top             =   2680
      Width           =   615
   End
   Begin VB.Label Answer4Label 
      Caption         =   "Answer 4"
      Height          =   255
      Left            =   3600
      TabIndex        =   17
      Top             =   5040
      Width           =   1095
   End
   Begin VB.Label Answer3Label 
      Caption         =   "Answer 3"
      Height          =   255
      Left            =   3600
      TabIndex        =   13
      Top             =   4320
      Width           =   1095
   End
   Begin VB.Label Answer2Label 
      Caption         =   "Answer 2"
      Height          =   255
      Left            =   3600
      TabIndex        =   12
      Top             =   3600
      Width           =   1095
   End
   Begin VB.Label Answer1Label 
      Caption         =   "Answer 1"
      Height          =   255
      Left            =   3600
      TabIndex        =   11
      Top             =   2880
      Width           =   1095
   End
   Begin VB.Label QuestionLine3Label 
      Caption         =   "Question Line 3"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   4320
      Width           =   1335
   End
   Begin VB.Label QuestionLine2Label 
      Caption         =   "Question Line 2"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   3600
      Width           =   1335
   End
   Begin VB.Label QuestionLine1Label 
      Caption         =   "Question Line 1"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2880
      Width           =   1215
   End
   Begin VB.Label QuestionListLabel 
      Caption         =   "Question List"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   975
   End
   Begin VB.Menu File 
      Caption         =   "&File"
      Begin VB.Menu NewQACFile 
         Caption         =   "New QAC File"
         Shortcut        =   ^N
      End
      Begin VB.Menu OpenQACFile 
         Caption         =   "Open QAC File..."
         Shortcut        =   ^O
      End
      Begin VB.Menu FileMenuDivider1 
         Caption         =   "-"
      End
      Begin VB.Menu SaveQACFile 
         Caption         =   "Save QAC File"
         Enabled         =   0   'False
         Shortcut        =   ^S
      End
      Begin VB.Menu SaveQACFileAs 
         Caption         =   "Save QAC File As..."
         Enabled         =   0   'False
         Shortcut        =   {F12}
      End
      Begin VB.Menu FileMenuDivider2 
         Caption         =   "-"
      End
      Begin VB.Menu Exit 
         Caption         =   "Exit"
         Shortcut        =   ^Q
      End
   End
   Begin VB.Menu Help 
      Caption         =   "&Help"
      Begin VB.Menu HowToUseQACEditor 
         Caption         =   "How To Use..."
         Shortcut        =   ^H
      End
      Begin VB.Menu HelpMenuDivider1 
         Caption         =   "-"
      End
      Begin VB.Menu AboutQACEditor 
         Caption         =   "About..."
      End
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub AboutQACEditor_Click()

  frmAbout.Show

End Sub

Private Sub ClearFields_Click()

    ' Clear all fields and radio buttons
    QuestionLine1.Text = ""
    QuestionLine2.Text = ""
    QuestionLine3.Text = ""
    CorrectAnswer1.Value = False
    CorrectAnswer2.Value = False
    CorrectAnswer3.Value = False
    CorrectAnswer4.Value = False
    Answer1.Text = ""
    Answer2.Text = ""
    Answer3.Text = ""
    Answer4.Text = ""

End Sub

Private Sub DeleteQuestion_Click()

    ' Make sure they want to delete the question, and do it if so
    If MsgBox("Are you sure you want to delete this question?", vbYesNoCancel, "Verify") = vbYes Then

        ' Delete it from the array and move all array elements above it (if any) down one to get rid of the empty element
        For i = QuestionList.ListIndex + 1 To NumberOfQuestions - 1
            QACs(i).Answer1 = QACs(i + 1).Answer1
            QACs(i).Answer2 = QACs(i + 1).Answer2
            QACs(i).Answer3 = QACs(i + 1).Answer3
            QACs(i).Answer4 = QACs(i + 1).Answer4
            QACs(i).CategoryKey = QACs(i + 1).CategoryKey
            QACs(i).CorrectAnswer = QACs(i + 1).CorrectAnswer
            QACs(i).QuestionLine1 = QACs(i + 1).QuestionLine1
            QACs(i).QuestionLine2 = QACs(i + 1).QuestionLine2
            QACs(i).QuestionLine3 = QACs(i + 1).QuestionLine3
        Next i

        ' Delete the item from the listbox and change the count
        QuestionList.RemoveItem (QuestionList.ListIndex)
        NumberOfQuestions = NumberOfQuestions - 1
        StatusBar.Panels(1).Text = "Number Of Questions: " & NumberOfQuestions
               
        ' Change back to New Question edit mode
        EditMode = emNew
        UpdateEditModeStatus
        
        ' Clear the fields by calling the Click event of the ClearFields button (so we're ready for another new question)
        ClearFields_Click
        
        ' Turn the Delete Question back off
        DeleteQuestion.Enabled = False
        DirtyDataFlag = True
        
    End If

End Sub

Private Sub Exit_Click()

    ' Exit the program
    End

End Sub


Private Sub Form_Load()

    DoingLoad = True
    StatusBar.Panels(1).Style = sbrText
    StatusBar.Panels(1).Alignment = sbrLeft
    StatusBar.Panels(1).AutoSize = sbrSpring
    StatusBar.Panels.Add
    StatusBar.Panels(2).Style = sbrText
    StatusBar.Panels(2).Alignment = sbrLeft
    StatusBar.Panels(2).AutoSize = sbrNoAutoSize
    StatusBar.Panels(2).Width = 2500
    StatusBar.Panels.Add
    StatusBar.Panels(3).Style = sbrCaps
    StatusBar.Panels(3).AutoSize = sbrContents
    StatusBar.Panels(3).Width = 1000
    StatusBar.Panels(3).Alignment = sbrCenter
    StatusBar.Panels.Add
    StatusBar.Panels(4).Style = sbrNum
    StatusBar.Panels(4).AutoSize = sbrContents
    StatusBar.Panels(4).Width = 1000
    StatusBar.Panels(4).Alignment = sbrCenter
    StatusBar.Panels.Add
    StatusBar.Panels(5).Style = sbrScrl
    StatusBar.Panels(5).AutoSize = sbrContents
    StatusBar.Panels(5).Width = 1000
    StatusBar.Panels(5).Alignment = sbrCenter
    UpdateNumberOfQuestionsStatus
    DoingLoad = False
    UpdateEditModeStatus

End Sub

Private Sub Form_Unload(Cancel As Integer)

  ' Make sure they want to leave if the data is dirty
  If Not VerifyExit Then Cancel = 1

End Sub

Private Sub HowToUseQACEditor_Click()

  frmHowToUse.Show

End Sub

Private Sub NewQACFile_Click()

  If VerifyExit Then

    ' Clear the QACs array and set the question count to zero
    Erase QACs
    NumberOfQuestions = 0
    UpdateNumberOfQuestionsStatus
    DirtyDataFlag = False
    
    ' Clear the Questions listbox
    QuestionList.Clear
    
    ' Enable the Questions list box and the New Question button
    QuestionList.BackColor = vbWindowBackground
    QuestionList.Enabled = True
        
    ' Setup our fields the default way
    SetupFields True
    
    ' Correction: disable Delete button
    DeleteQuestion.Enabled = False
    
    ' Start in the New Question edit mode
    EditMode = emNew
    UpdateEditModeStatus

    ' Set up the menu items appropriately
    SaveQACFile.Enabled = False
    SaveQACFileAs.Enabled = True
    
    ' Set filename and titlebar text
    Filename = "untitled.qac"
    MainForm.Caption = Filename & " - Invasion: Trivia QAC Editor"
    
  End If

End Sub


Private Sub OpenQACFile_Click()

  If VerifyExit Then

    ' Ask the user what file they want to open and call the open function (abort if Cancel clicked)
    On Error GoTo CancelHandler
    CommonDialog.ShowOpen
    Filename = CommonDialog.Filename
    If OpenQACFileFunction <> 0 Then Exit Sub
    On Error GoTo 0

    ' Clear the Questions listbox
    QuestionList.Clear
    DirtyDataFlag = False

    ' Add all questions to the listbox
    For i = 1 To NumberOfQuestions
        addString = ""
        addString = addString & QACs(i).QuestionLine1 & " " & QACs(i).QuestionLine2 & " " & QACs(i).QuestionLine3
        addString = addString & "  (  "
        If QACs(i).CorrectAnswer = 1 Then
          addString = addString & ">" & QACs(i).Answer1 & "<"
        Else
          addString = addString & QACs(i).Answer1
        End If
        addString = addString & ",  "
        If QACs(i).CorrectAnswer = 2 Then
          addString = addString & ">" & QACs(i).Answer2 & "<"
        Else
          addString = addString & QACs(i).Answer2
        End If
        addString = addString & ",  "
        If QACs(i).CorrectAnswer = 3 Then
          addString = addString & ">" & QACs(i).Answer3 & "<"
        Else
          addString = addString & QACs(i).Answer3
        End If
        addString = addString & ",  "
        If QACs(i).CorrectAnswer = 4 Then
          addString = addString & ">" & QACs(i).Answer4 & "<"
        Else
          addString = addString & QACs(i).Answer4
        End If
        addString = addString & "  )"
        QuestionList.AddItem addString
    Next i
    UpdateNumberOfQuestionsStatus
       
    ' Set up the fields and menus
    SetupFields False
    QuestionList.Enabled = True
    QuestionList.BackColor = vbWindowBackground
    SaveQACFile.Enabled = True
    SaveQACFileAs.Enabled = True
    MainForm.Caption = Filename & " - Invasion: Trivia QAC Editor"
       
  End If
       
CancelHandler:

    On Error GoTo 0

End Sub

Private Sub QuestionList_Click()

    ' Populate the edit fields with the data from the clicked element and set up the buttons properly
    If QuestionList.Text <> "" Then
        SetupFields True
        DeleteQuestion.Enabled = True
        QuestionLine1.Text = QACs(QuestionList.ListIndex + 1).QuestionLine1
        QuestionLine2.Text = QACs(QuestionList.ListIndex + 1).QuestionLine2
        QuestionLine3.Text = QACs(QuestionList.ListIndex + 1).QuestionLine3
        If QACs(QuestionList.ListIndex + 1).CorrectAnswer = 1 Then CorrectAnswer1.Value = True
        If QACs(QuestionList.ListIndex + 1).CorrectAnswer = 2 Then CorrectAnswer2.Value = True
        If QACs(QuestionList.ListIndex + 1).CorrectAnswer = 3 Then CorrectAnswer3.Value = True
        If QACs(QuestionList.ListIndex + 1).CorrectAnswer = 4 Then CorrectAnswer4.Value = True
        Answer1.Text = QACs(QuestionList.ListIndex + 1).Answer1
        Answer2.Text = QACs(QuestionList.ListIndex + 1).Answer2
        Answer3.Text = QACs(QuestionList.ListIndex + 1).Answer3
        Answer4.Text = QACs(QuestionList.ListIndex + 1).Answer4
        EditMode = emEdit
        UpdateEditModeStatus
    End If
    
End Sub

Private Sub SaveQACFile_Click()

    ' Just call the file save function because the global Filename variable is already populated properly by now
    SaveQACFileFunction

End Sub

Private Sub SaveQACFileAs_Click()

    ' Ask the user where they want to save it and under what name (abort if Cancel clicked)
    CommonDialog.Filename = Filename
    On Error GoTo CancelHandler
    CommonDialog.ShowSave
    Filename = CommonDialog.Filename
    SaveQACFileFunction
    SaveQACFile.Enabled = True
    MainForm.Caption = Filename & " - Invasion: Trivia QAC Editor"
    DirtyDataFlag = False
    
CancelHandler:
    On Error GoTo 0
    
End Sub

Private Sub SaveQuestion_Click()

    ' Make sure there is still a spot for a question
    If NumberOfQuestions >= 1000 Then
        MsgBox "You have reached the maximum of 1,000 questions in a single QAC file." & Chr(13) & Chr(13) & "You will need to delete a question before adding another.", vbOKOnly, "No more questions allowed"
        Exit Sub
    End If

    ' Get what the user entered
    Answer1 = Trim(Answer1.Text)
    Answer2 = Trim(Answer2.Text)
    Answer3 = Trim(Answer3.Text)
    Answer4 = Trim(Answer4.Text)
    CategoryKey = 0
    CorrectAnswer = 0
    If CorrectAnswer1.Value = True Then CorrectAnswer = 1
    If CorrectAnswer2.Value = True Then CorrectAnswer = 2
    If CorrectAnswer3.Value = True Then CorrectAnswer = 3
    If CorrectAnswer4.Value = True Then CorrectAnswer = 4
    QuestionLine1 = Trim(QuestionLine1.Text)
    QuestionLine2 = Trim(QuestionLine2.Text)
    QuestionLine3 = Trim(QuestionLine3.Text)
    
    ' Make sure they filled the Question boxes in an allowed way
    If QuestionLine1 = "" And QuestionLine2 = "" And QuestionLine3 = "" Then
        MsgBox "Please enter at least the first line of the question", vbOKOnly, "No question entered"
        QuestionLine1.SetFocus
        Exit Sub
    End If
    If QuestionLine1 <> "" And QuestionLine2 = "" And QuestionLine3 <> "" Then
        MsgBox "Please fill the lines of the question in sequence", vbOKOnly, "Problem with question"
        QuestionLine1.SetFocus
        Exit Sub
    End If
    If QuestionLine1 = "" And (QuestionLine2 <> "" Or QuestionLine3 <> "") Then
        MsgBox "Please fill the lines of the question in sequence", vbOKOnly, "Problem with question"
        QuestionLine1.SetFocus
        Exit Sub
    End If
    
    ' Make sure they entered something for all four answers
    If Answer1 = "" Then
        MsgBox "Please enter something for Answer 1", vbOKOnly, "Problem with answer 1"
        Answer1.SetFocus
        Exit Sub
    End If
    If Answer2 = "" Then
        MsgBox "Please enter something for Answer 2", vbOKOnly, "Problem with answer 2"
        Answer2.SetFocus
        Exit Sub
    End If
    If Answer3 = "" Then
        MsgBox "Please enter something for Answer 3", vbOKOnly, "Problem with answer 3"
        Answer3.SetFocus
        Exit Sub
    End If
    If Answer4 = "" Then
        MsgBox "Please enter something for Answer 4", vbOKOnly, "Problem with answer 4"
        Answer4.SetFocus
        Exit Sub
    End If

    ' Make sure they selected a correct answer
    If CorrectAnswer = 0 Then
        MsgBox "Please indicate the correct answer", vbOKOnly, "No correct answer indicated"
        CorrectAnswer1.SetFocus
        Exit Sub
    End If
    
    ' Save the data to our array and listbox according to the edit mode
    Indexer = 0
    If EditMode = emNew Then
        ' We're in add mode, so bump up the questions count and add the question to the end of the listbox
        NumberOfQuestions = NumberOfQuestions + 1
        UpdateNumberOfQuestionsStatus
        Indexer = NumberOfQuestions
        QuestionList.AddItem QuestionLine1 & " " & QuestionLine2 & " " & QuestionLine3
    Else
        ' We're in edit mode... remove the current listbox item and add our question in at that index
        Indexer = QuestionList.ListIndex
        QuestionList.RemoveItem Indexer
        QuestionList.AddItem QuestionLine1 & " " & QuestionLine2 & " " & QuestionLine3, Indexer
        Indexer = Indexer + 1 ' So we save to the correct array element
    End If
    ' Save to the array... Indexer is either = NumberOfQuestions or the correct index based on the above
    QACs(Indexer).Answer1 = Answer1
    QACs(Indexer).Answer2 = Answer2
    QACs(Indexer).Answer3 = Answer3
    QACs(Indexer).Answer4 = Answer4
    QACs(Indexer).CategoryKey = CategoryKey
    QACs(Indexer).CorrectAnswer = CorrectAnswer
    QACs(Indexer).QuestionLine1 = QuestionLine1
    QACs(Indexer).QuestionLine2 = QuestionLine2
    QACs(Indexer).QuestionLine3 = QuestionLine3
    
    ' Change back to New Question edit mode and turn the Delete Question button back off
    EditMode = emNew
    UpdateEditModeStatus
    DeleteQuestion.Enabled = False
    
    DirtyDataFlag = True
    
    ' Clear the fields by calling the Click event of the ClearFields button (so we're ready for another new question)
    ClearFields_Click

End Sub


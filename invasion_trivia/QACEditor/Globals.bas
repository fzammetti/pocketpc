Attribute VB_Name = "Globals"

' Our custom type that describes a QAC
Public Type QAC
    Answer1 As String
    Answer2 As String
    Answer3 As String
    Answer4 As String
    CategoryKey As Integer
    CorrectAnswer As Integer
    QuestionLine1 As String
    QuestionLine2 As String
    QuestionLine3 As String
End Type

' Our array of QACs
Public QACs(1000) As QAC

' This is used exactly once when the program is loading so we can display N/A for the number of questions
Public DoingLoad As Boolean

' Counter of the number of QACs in the current QAC file
Public NumberOfQuestions As Integer

' Constants for what edit mode we're in
Public Const emNone = 0
Public Const emNew = 1
Public Const emEdit = 2

' Name of the currently opened QAC file
Public Filename As String

' This is set to true when there is data to potentially save
Public DirtyDataFlag As Boolean

' Tells what edit mode we're in from above possible value
Public EditMode As Integer

Public Sub Main()

    ' Some basic initialization
    EditMode = emNone
    Erase QACs
    NumberOfQuestions = 0
    Filename = "untitled.qac"
    DirtyDataFlag = False
    MainForm.Show

End Sub

Public Sub SetupFields(EnabledDisabledFlag As Boolean)

    If EnabledDisabledFlag = True Then
        FieldBGColor = vbWindowBackground
    Else
        FieldBGColor = vbButtonFace
    End If
    
    With MainForm
    
        ' Questions listbox
        .QuestionList.Enabled = EnabledDisabledFlag
        .QuestionList.BackColor = FieldBGColor
    
        ' Question Line edit boxes and clear them
        .QuestionLine1.BackColor = FieldBGColor
        .QuestionLine1.Enabled = EnabledDisabledFlag
        .QuestionLine1.Text = ""
        .QuestionLine2.BackColor = FieldBGColor
        .QuestionLine2.Enabled = EnabledDisabledFlag
        .QuestionLine2.Text = ""
        .QuestionLine3.BackColor = FieldBGColor
        .QuestionLine3.Enabled = EnabledDisabledFlag
        .QuestionLine3.Text = ""
        
        ' Enable the Correct Answer radio option buttons and clear them
        .CorrectAnswer1.Enabled = EnabledDisabledFlag
        .CorrectAnswer2.Enabled = EnabledDisabledFlag
        .CorrectAnswer3.Enabled = EnabledDisabledFlag
        .CorrectAnswer4.Enabled = EnabledDisabledFlag
        .CorrectAnswer1.Value = False
        .CorrectAnswer2.Value = False
        .CorrectAnswer3.Value = False
        .CorrectAnswer4.Value = False
        
        ' Enable the Answer edit boxes and clear them
        .Answer1.BackColor = FieldBGColor
        .Answer1.Enabled = EnabledDisabledFlag
        .Answer1.Text = ""
        .Answer2.BackColor = FieldBGColor
        .Answer2.Enabled = EnabledDisabledFlag
        .Answer2.Text = ""
        .Answer3.BackColor = FieldBGColor
        .Answer3.Enabled = EnabledDisabledFlag
        .Answer3.Text = ""
        .Answer4.BackColor = FieldBGColor
        .Answer4.Enabled = EnabledDisabledFlag
        .Answer4.Text = ""
        
        ' Enable tne Save Question and Clear Fields buttons
        .SaveQuestion.Enabled = EnabledDisabledFlag
        .DeleteQuestion.Enabled = EnabledDisabledFlag
        .ClearFields.Enabled = EnabledDisabledFlag
    
    End With
    
End Sub

Public Sub SaveQACFileFunction()

    ' QAC File format:
    ' ----------------
    '
    ' 5 bytes ..... File identified ("ITQAC")
    ' 1 byte ...... Major version #
    ' 1 byte ...... Minor version #
    ' 10 bytes .... Expansion padding (spaces)
    '
    ' Note: Category information is dummied for now
    '
    ' Struct { // Repeats x times (25 max)
    '   1 Byte .... Category key
    '   xx bytes .. Category name (16 bytes max)
    '   1 byte .... Value 254 - "End of category" indicator
    ' }
    '
    ' 1 byte ...... Value 255 - "End of category list" indicator
    '
    ' Struct { // Repeats x times (1000 max)
    '   1 byte .... Category key
    '   xx bytes .. Question (77 bytes max)
    '   1 byte .... Value 254 - "End of question" indicator
    '   xx bytes .. Answer 1 (26 bytes max)
    '   1 byte .... Value 254 - "End of answer" indicator
    '   xx bytes .. Answer 2 (26 bytes max)
    '   1 byte .... Value 254 - "End of answer" indicator
    '   xx bytes .. Answer 3 (26 bytes max)
    '   1 byte .... Value 254 - "End of answer" indicator
    '   xx bytes .. Answer 4 (26 bytes max)
    '   1 byte .... Value 254 - "End of answer" indicator
    '   1 byte .... Correct answer key (values 1, 2, 3 or 4)
    ' }
    '
    ' 1 byte ...... Value 255 - "End of data" indicator
 
    FileNum = FreeFile
    If Dir(Filename) <> "" Then
        Kill Filename
    End If
    Open Filename For Output As #FileNum

    ' Header
    Print #FileNum, "ITQAC"; ' (I)nvasion: (T)rivia (Q)uestions/(A)nswers/(C)ategories
    Print #FileNum, Chr$(1); ' Major version #
    Print #FileNum, Chr$(0); ' Minor version #
    Print #FileNum, "          "; ' Expansion padding

    ' Categories (dummy data)
    Print #FileNum, Chr$(0); ' Category key
    Print #FileNum, "General Knowledge"; ' Category name
    Print #FileNum, Chr$(254); ' End of category indicator

    ' End of categories indicator
    Print #FileNum, Chr$(255);

    ' QAs

    For i = 1 To NumberOfQuestions
        Print #FileNum, Chr$(0); ' Category key
        Print #FileNum, QACs(i).QuestionLine1 & "~" & QACs(i).QuestionLine2 & "~" & QACs(i).QuestionLine3; ' Question
        Print #FileNum, Chr$(254); ' End of question indicator
        Print #FileNum, QACs(i).Answer1; ' Answer 1
        Print #FileNum, Chr$(254); ' End of question indicator
        Print #FileNum, QACs(i).Answer2; ' Answer 2
        Print #FileNum, Chr$(254); ' End of question indicator
        Print #FileNum, QACs(i).Answer3; ' Answer 3
        Print #FileNum, Chr$(254); ' End of question indicator
        Print #FileNum, QACs(i).Answer4; ' Answer 4
        Print #FileNum, Chr$(254); ' End of question indicator
        Print #FileNum, Trim(Chr$(QACs(i).CorrectAnswer)); ' Correct answer (values 1, 2, 3 or 4)
    Next i

    Print #FileNum, Chr$(255); ' End of data indicator

    Close #FileNum

End Sub
Function OpenQACFileFunction()

    ' Clear the QACs array and set the question count to zero
    Erase QACs
    NumberOfQuestions = 0
    
    ' Open the file
    FileNum = FreeFile
    Open Filename For Binary As #FileNum

    ' Header: Identifier
    Dim QAC_Identifier As String
    QAC_Identifier = String(5, "*")
    Get #FileNum, , QAC_Identifier
    
    ' Header: Major Version Number
    Dim QAC_MajorVersionNumber As String
    QAC_MajorVersionNumber = String(1, "*")
    Get #FileNum, , QAC_MajorVersionNumber
    
    ' Header: Minor Version Number
    Dim QAC_MinorVersionNumber As String
    QAC_MinorVersionNumber = String(1, "*")
    Get #FileNum, , QAC_MinorVersionNumber
    
    ' Header: Expansion Padding
    Dim QAC_ExpansionPadding As String
    QAC_ExpansionPadding = String(10, "*")
    Get #FileNum, , QAC_ExpansionPadding
    
    ' Header checks
    If QAC_Identifier <> "ITQAC" Or Asc(QAC_MajorVersionNumber) <> 1 Or Asc(QAC_MinorVersionNumber) <> 0 Or QAC_ExpansionPadding <> "          " Then
        MsgBox "This file does not appear to be a valid QAC file or" & vbCr & "it was created with a different version of QACEditor."
        OpenQACFileFunction = -1
        Close #FileNum
        Exit Function
    End If

    ' Categories (dummy data, just skip it all until we hit the end-of-categories indicator)
    Dim QAC_CatNextChar As String
    QAC_CatNextChar = String(1, "*")
    Get #FileNum, , QAC_CatNextChar
    Do While Asc(QAC_CatNextChar) <> 255
        Get #FileNum, , QAC_CatNextChar
    Loop

    ' QAs
    Dim QAC_NextChar As String
    QAC_NextChar = String(1, "*")
    Dim QAC_CategoryKey As String
    QAC_CategoryKey = String(1, "*")
    Dim QAC_Question As String
    Dim QAC_Answer1 As String
    Dim QAC_Answer2 As String
    Dim QAC_Answer3 As String
    Dim QAC_Answer4 As String
    Dim QAC_CorrectAnswer As String
    Dim SplitQuestion() As String
    QAC_CorrectAnswer = String(1, "*")

    ' Start by getting the first category key
    Get #FileNum, , QAC_CategoryKey

    ' Start our loop until we hit the end of data indicator
    Do While Asc(QAC_CategoryKey) <> 255

        ' Iterate the question
        QAC_Question = ""
        Get #FileNum, , QAC_NextChar
        Do While Asc(QAC_NextChar) <> 254
            QAC_Question = QAC_Question & QAC_NextChar
            Get #FileNum, , QAC_NextChar
        Loop

        ' Iterate the first answer
        QAC_Answer1 = ""
        Get #FileNum, , QAC_NextChar
        Do While Asc(QAC_NextChar) <> 254
            QAC_Answer1 = QAC_Answer1 & QAC_NextChar
            Get #FileNum, , QAC_NextChar
        Loop

        ' Iterate the second answer
        QAC_Answer2 = ""
        Get #FileNum, , QAC_NextChar
        Do While Asc(QAC_NextChar) <> 254
            QAC_Answer2 = QAC_Answer2 & QAC_NextChar
            Get #FileNum, , QAC_NextChar
        Loop

        ' Iterate the third answer
        QAC_Answer3 = ""
        Get #FileNum, , QAC_NextChar
        Do While Asc(QAC_NextChar) <> 254
            QAC_Answer3 = QAC_Answer3 & QAC_NextChar
            Get #FileNum, , QAC_NextChar
        Loop

        ' Iterate the fourth answer
        QAC_Answer4 = ""
        Get #FileNum, , QAC_NextChar
        Do While Asc(QAC_NextChar) <> 254
            QAC_Answer4 = QAC_Answer4 & QAC_NextChar
            Get #FileNum, , QAC_NextChar
        Loop
        
        ' Correct answer
        Get #FileNum, , QAC_CorrectAnswer

        ' Now we should have everything, go ahead and add it to our array
        NumberOfQuestions = NumberOfQuestions + 1
        QACs(NumberOfQuestions).Answer1 = QAC_Answer1
        QACs(NumberOfQuestions).Answer2 = QAC_Answer2
        QACs(NumberOfQuestions).Answer3 = QAC_Answer3
        QACs(NumberOfQuestions).Answer4 = QAC_Answer4
        QACs(NumberOfQuestions).CategoryKey = Asc(QAC_CategoryKey)
        QACs(NumberOfQuestions).CorrectAnswer = Asc(QAC_CorrectAnswer)
        Erase SplitQuestion
        SplitQuestion = Split(QAC_Question, "~")
        QACs(NumberOfQuestions).QuestionLine1 = SplitQuestion(0)
        If UBound(SplitQuestion) > 0 Then QACs(NumberOfQuestions).QuestionLine2 = SplitQuestion(1)
        If UBound(SplitQuestion) > 1 Then QACs(NumberOfQuestions).QuestionLine3 = SplitQuestion(2)
               
        ' Get the next Category Key
        Get #FileNum, , QAC_CategoryKey
        
    Loop

    Close #FileNum

    ' Exit cleanly
    OpenQACFileFunction = 0

End Function

Public Sub UpdateNumberOfQuestionsStatus()

  ' Update the status bar display of the number of questions
  If DoingLoad Then ' Only do this once when the program loads
    MainForm.StatusBar.Panels(1).Text = "Number Of Questions: N/A"
  Else ' This is what we do any other time
    MainForm.StatusBar.Panels(1).Text = "Number Of Questions: " & NumberOfQuestions
  End If

End Sub

Public Sub UpdateEditModeStatus()

  ' Update the status bar to tell what edit mode we're in
  strOut = ""
  If EditMode = emNone Then strOut = "N/A"
  If EditMode = emNew Then strOut = "New Question"
  If EditMode = emEdit Then strOut = "Edit Question"
  MainForm.StatusBar.Panels(2).Text = "Edit Mode: " & strOut
  
End Sub

Public Function VerifyExit() As Boolean

  VerifyExit = True
  ' If data is dirty and they don't want to lose changes, get outta here
  If DirtyDataFlag Then
    If MsgBox("You have changes which have not been saved." & vbCr & _
              "Continuing this action will result in those changes being lost." & vbCr & vbCr & _
              "Are you sure you want to continue?", vbYesNoCancel, "Verify") <> vbYes Then
                VerifyExit = False
    End If
  End If

End Function

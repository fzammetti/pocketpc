VERSION 5.00
Begin VB.Form frmHowToUse 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "How To Use..."
   ClientHeight    =   5970
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   7695
   Icon            =   "frmHowToUse.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5970
   ScaleWidth      =   7695
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdOK 
      Cancel          =   -1  'True
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   345
      Left            =   6360
      TabIndex        =   1
      Top             =   5520
      Width           =   1260
   End
   Begin VB.TextBox txtHowToUse 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5295
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Text            =   "frmHowToUse.frx":0442
      Top             =   120
      Width           =   7455
   End
End
Attribute VB_Name = "frmHowToUse"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdOK_Click()

  Unload Me

End Sub

Private Sub Form_Load()

  txtHowToUse = ""
  txtHowToUse = txtHowToUse & "INTRODUCTION" & vbCrLf
  txtHowToUse = txtHowToUse & "---------------------------------------------------------------------------------------------" & vbCrLf
  txtHowToUse = txtHowToUse & "Using QAC Editor couldn't be easier (unless it included a direct telepathic "
  txtHowToUse = txtHowToUse & "nueral link to your brain, but the damage would be irreversible, so this is "
  txtHowToUse = txtHowToUse & "probably better, all things considered!)" & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "STARTING A NEW QAC FILE" & vbCrLf
  txtHowToUse = txtHowToUse & "---------------------------------------------------------------------------------------------" & vbCrLf
  txtHowToUse = txtHowToUse & "When you select New QAC File from the main menu, the entry controls will become "
  txtHowToUse = txtHowToUse & "active.  You can now begin entering questions. Simply go into the Question Line 1 "
  txtHowToUse = txtHowToUse & "edit box and enter some text.  You must always fill in the first line of the "
  txtHowToUse = txtHowToUse & "question, lines 2 and 3 are optional, and you must fill them in an allowed "
  txtHowToUse = txtHowToUse & "manner (i.e., you must fill line 1 and 2 before you can fill line 3).  Don't "
  txtHowToUse = txtHowToUse & "worry too much about this, the editor will catch this if you screw it up." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "Note that each line of the question allows a maximum of 25 characters to be entered." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "After you enter the question, you must fill in all four possible answers, making "
  txtHowToUse = txtHowToUse & "one and only one of them the correct answer.  Do this by selecting the radio "
  txtHowToUse = txtHowToUse & "option next to the correct answer.  Again, the editor will tell you if you "
  txtHowToUse = txtHowToUse & "forget to select a correct answer or do not fill in all four answer boxes." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "Note that each answer can be a maximum of 26 character long." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "Naturally, it's your job to do the research and make sure only one of the answers "
  txtHowToUse = txtHowToUse & "really IS correct.  The editor isn't all-knowing! (Although that's slated for version 2.0)" & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "When you are happy with your input, click the Save Question button and your "
  txtHowToUse = txtHowToUse & "question will be added to the list of questions box at the top.  At this point "
  txtHowToUse = txtHowToUse & "you can enter another question following the same procedure." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "If you need to make changes to a question you already entered, or you want to "
  txtHowToUse = txtHowToUse & "delete a question, click it in the list box at the top.  Note that the Edit Mode "
  txtHowToUse = txtHowToUse & "shown in the bottom status bar changes from New Question mode to Edit Question mode."
  txtHowToUse = txtHowToUse & "Simply make whatever changes you want and click Save Question to update it.  Click"
  txtHowToUse = txtHowToUse & "Delete Question to, yep, you guessed it!, delete the question!  Note that "
  txtHowToUse = txtHowToUse & "you MUST save the question, even if you make no changes, before you can add a "
  txtHowToUse = txtHowToUse & "new question again!" & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "Once you have entered all the questions you want (to a maximum of 1,000), select "
  txtHowToUse = txtHowToUse & "the Save QAC File As menu option on the File menu.  Browse to the directory you "
  txtHowToUse = txtHowToUse & "want to save to and give the file a real name and save away.  Once you save "
  txtHowToUse = txtHowToUse & "the file using Save As, you will from then on be able to use the Save QAC File "
  txtHowToUse = txtHowToUse & "menu item, which will save to the location and with the name you entered previously." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "LOADING AND EDITING AN EXISTING QAC FILE" & vbCrLf
  txtHowToUse = txtHowToUse & "---------------------------------------------------------------------------------------------" & vbCrLf
  txtHowToUse = txtHowToUse & "Now, as for loading and toying with existing QAC files..." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "Simply select Load QAC File from the File menu, browse to the apppropriate directory "
  txtHowToUse = txtHowToUse & "and select the file to load.  In a second or two the list box will be populated with all "
  txtHowToUse = txtHowToUse & "the questions in the file.  Edit and add as described above and save your changes "
  txtHowToUse = txtHowToUse & "also as described above." & vbCrLf & vbCrLf
  txtHowToUse = txtHowToUse & "The Clear Fields button is always available and will, obviously enough, clear the "
  txtHowToUse = txtHowToUse & "entry fields on the screen.  It will NOT save these changes though, you must still do "
  txtHowToUse = txtHowToUse & "that with the Save Question button."
  

End Sub

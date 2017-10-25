VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About..."
   ClientHeight    =   5070
   ClientLeft      =   2340
   ClientTop       =   1935
   ClientWidth     =   7515
   ClipControls    =   0   'False
   Icon            =   "frmAbout.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3499.404
   ScaleMode       =   0  'User
   ScaleWidth      =   7056.972
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame Frame3 
      Height          =   28
      Left            =   3840
      TabIndex        =   11
      Top             =   3360
      Width           =   3555
   End
   Begin VB.Frame Frame2 
      Height          =   28
      Left            =   3840
      TabIndex        =   10
      Top             =   2280
      Width           =   3555
   End
   Begin VB.Frame Frame1 
      Height          =   28
      Left            =   3840
      TabIndex        =   9
      Top             =   960
      Width           =   3555
   End
   Begin VB.CommandButton cmdOK 
      Cancel          =   -1  'True
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   345
      Left            =   6120
      TabIndex        =   0
      Top             =   4560
      Width           =   1260
   End
   Begin VB.Image Image1 
      BorderStyle     =   1  'Fixed Single
      Height          =   4860
      Left            =   120
      Picture         =   "frmAbout.frx":0442
      Top             =   120
      Width           =   3660
   End
   Begin VB.Label Label5 
      Caption         =   "Visit Omnytex Technologies on the web at http://www.omnytex.com and Crackhead Creations at http://www.planetvolpe.com."
      ForeColor       =   &H00000000&
      Height          =   690
      Left            =   3960
      TabIndex        =   8
      Top             =   3600
      Width           =   3405
   End
   Begin VB.Label Label4 
      Caption         =   "Crackhead Creations"
      ForeColor       =   &H00000000&
      Height          =   210
      Left            =   3960
      TabIndex        =   7
      Top             =   1920
      Width           =   3405
   End
   Begin VB.Label Label3 
      Caption         =   "And"
      ForeColor       =   &H00000000&
      Height          =   210
      Left            =   3960
      TabIndex        =   6
      Top             =   1680
      Width           =   3405
   End
   Begin VB.Label Label2 
      Caption         =   "Omnytex Technologies"
      ForeColor       =   &H00000000&
      Height          =   210
      Left            =   3960
      TabIndex        =   5
      Top             =   1440
      Width           =   3405
   End
   Begin VB.Label Label1 
      Caption         =   "(C)opyright 2003"
      ForeColor       =   &H00000000&
      Height          =   210
      Left            =   3960
      TabIndex        =   4
      Top             =   1200
      Width           =   3405
   End
   Begin VB.Label lblDescription 
      Caption         =   "This is a Visual Basic 6.0 application that allows people to create QAC files for use with the PocketPC game Invasion: Trivia."
      ForeColor       =   &H00000000&
      Height          =   690
      Left            =   3960
      TabIndex        =   1
      Top             =   2520
      Width           =   3405
   End
   Begin VB.Label lblTitle 
      Caption         =   "Invasion: Trivia QAC Editor"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   360
      Left            =   3960
      TabIndex        =   2
      Top             =   240
      Width           =   3405
   End
   Begin VB.Label lblVersion 
      Caption         =   "Version 1.0"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Left            =   3960
      TabIndex        =   3
      Top             =   600
      Width           =   3405
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdOK_Click()

  Unload Me

End Sub


'for 'Form'
Imports System.Windows.Forms

'.net callble dll created by using tlbimp.exe utility
Imports AutomationServerTypeLibForDotNet

Public Class VBAutoamtion
    Inherits Form
    Public Sub New()
        Dim MyIDispatch As Object
        Dim MyRef As New CMyMathClass
        MyIDispatch = MyRef
        Dim iNum1 = 175
        Dim iNum2 = 125
        Dim iSum = MyIDispatch.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum Of {0} And {1} is {2}", iNum1, iNum2, iSum)
        MsgBox(str)
        'Default Message Box With Only One Button "OK" 
        Dim iSub = MyIDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Subtraction Of {0} And {1} is {2}", iNum1, iNum2, iSum)
        MsgBox(str)

        End
    End Sub

    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutoamtion())
    End Sub
End Class



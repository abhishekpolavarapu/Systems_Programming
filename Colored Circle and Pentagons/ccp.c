#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/Label.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

Widget shell, panel, create_x, create_p, commands, topLabel;
Widget  quit, yes, no, bCreateX, bCloseX, bCreateP, bCloseP;
 
Arg wargs[1];
Display *display;
int screen;
long fgcolor, bgcolor;
XGCValues gcval;
GC draw;
Window window;
long childpid;


Colormap cmap;
char *green = "green";
char *red = "red";
XColor color, ignore;
Arg redwargs[1];
Arg greenwargs[1];

void quitCallback(Widget w, XtPointer clientData, XtPointer callData);
void yesCallback(Widget w, XtPointer clientData, XtPointer callData);
void noCallback(Widget w, XtPointer clientData, XtPointer callData);
void OpenXCallback(Widget w, XtPointer clientData, XtPointer callData);
void initInterface();
void CloseXCallback(Widget w, XtPointer clientData, XtPointer callData);
 
void ClosePCallback(Widget w, XtPointer clientData, XtPointer callData);
void OpenPCallback(Widget w, XtPointer clientData, XtPointer callData);
void ModalBox();
void ConfirmQuitCallback(Widget w, XtPointer clientData, XtPointer callData);

void main(int argc, char **argv)
{
	XtAppContext app;
	char *msg="   Colored Circle Pentagons  ";
	XmString       xmstr;
	shell = XtAppInitialize(&app, "Editor", NULL, 0,&argc, argv, NULL, NULL, 0);

	panel = XtCreateManagedWidget("panel", xmFormWidgetClass,shell, NULL, 0);
		
	
	display = XtDisplay(shell);
	screen = DefaultScreen(display);
	cmap = DefaultColormap(display, screen);
	
	xmstr = XmStringCreate ( msg, XmFONTLIST_DEFAULT_TAG ); 
	
	
	topLabel = XtVaCreateManagedWidget ( "topLabel", xmLabelWidgetClass, panel, XmNlabelString, xmstr, 
			    XmNtopAttachment, XmATTACH_FORM, 
                            XmNrightAttachment, XmATTACH_FORM,
			    XmNleftAttachment, XmATTACH_FORM, 
                            XmNbottomAttachment, XmATTACH_NONE, 
                            NULL ); 
	
	create_x =
		XtVaCreateManagedWidget("create_x", xmRowColumnWidgetClass, panel, XmNnumColumns, 3,
		XmNtopWidget, topLabel,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNrightAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_NONE,
		XmNbottomAttachment, XmATTACH_NONE, NULL);
	
	create_p =
		XtVaCreateManagedWidget("create_p", xmRowColumnWidgetClass,panel, XmNnumColumns, 3,
		 
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, topLabel,
		XmNrightAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_NONE,NULL);
	
	commands =
		XtVaCreateManagedWidget("commands", xmRowColumnWidgetClass, panel, XmNnumColumns, 3,
		XmNorientation, XmHORIZONTAL,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, create_x,
		XmNrightAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_NONE, NULL);
	
	bCreateX = XtCreateManagedWidget("Create XWindow", xmPushButtonWidgetClass,create_x, NULL, 0);
	bCloseX = XtCreateManagedWidget("Close XWindow", xmPushButtonWidgetClass,create_x, NULL, 0);
	 
	bCreateP = XtCreateManagedWidget("Create Python", xmPushButtonWidgetClass, create_p, NULL, 0);
	bCloseP = XtCreateManagedWidget("Close Python", xmPushButtonWidgetClass, create_p, NULL, 0);
	 
	
	no = XtCreateManagedWidget  ("      No       ", xmPushButtonWidgetClass, commands, NULL, 0);
	quit = XtCreateManagedWidget("      QUIT     ", xmPushButtonWidgetClass, commands, NULL, 0);
	yes = XtCreateManagedWidget ("      Yes      ", xmPushButtonWidgetClass, commands, NULL, 0);

	 
	XtAddCallback(bCreateX, XmNactivateCallback, OpenXCallback, NULL);
	XtAddCallback(bCloseX, XmNactivateCallback, CloseXCallback, NULL);
	
	XtAddCallback(bCreateP, XmNactivateCallback, OpenPCallback, NULL);
	XtAddCallback(bCloseP, XmNactivateCallback, ClosePCallback, NULL);

	XtAddCallback(quit, XmNactivateCallback,quitCallback, NULL);
	XtAddCallback(yes, XmNactivateCallback,yesCallback, NULL);
	XtAddCallback(no, XmNactivateCallback,noCallback, NULL);
	
	XtRealizeWidget(shell);
	//hide no, yes button
	XtUnmapWidget(no);
	XtUnmapWidget(yes);

	initInterface();

	XtAppMainLoop(app);
}

void initInterface(){

	XAllocNamedColor(display, cmap, green, &color, &ignore);
	XtSetArg(greenwargs[0], XmNbackground, color.pixel);
	XAllocNamedColor(display, cmap, red, &color, &ignore);
	XtSetArg(redwargs[0], XmNbackground, color.pixel);
	
	//Color buttons and disable close buttons
	XtVaSetValues(bCloseX, XmNsensitive, False, NULL);
	XtVaSetValues(bCreateX, XmNsensitive, True, NULL);
	XtSetValues(bCloseX, redwargs, 1);
	XtSetValues(bCreateX, greenwargs , 1);
	
	XtVaSetValues(bCloseP, XmNsensitive, False, NULL);
	XtVaSetValues(bCreateP, XmNsensitive, True, NULL);
	XtSetValues(bCloseP, redwargs, 1);
	XtSetValues(bCreateP, greenwargs , 1);
}

void quitCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	ModalBox();
}

void yesCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	/* No action is necessary, just exit. */
	exit(0);
}
void noCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	XtVaSetValues(quit, XmNsensitive, True, NULL);
	XtMapWidget(quit);
	XtUnmapWidget(no);
	XtUnmapWidget(yes);
}

void CloseXCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	XtVaSetValues(bCloseX, XmNsensitive, False, NULL);
	XtVaSetValues(bCreateX, XmNsensitive, True, NULL);
	XtSetValues(bCloseX, redwargs, 1);
	XtSetValues(bCreateX, greenwargs , 1);
	system ("pkill -9 xdraw");
}

void ClosePCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	XtVaSetValues(bCloseP, XmNsensitive, False, NULL);
	XtVaSetValues(bCreateP, XmNsensitive, True, NULL);
	XtSetValues(bCloseP, redwargs, 1);
	XtSetValues(bCreateP, greenwargs , 1);
	system ("pkill -9 python3");
}
void OpenXCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	XtVaSetValues(bCloseX, XmNsensitive, True, NULL);
	XtVaSetValues(bCreateX, XmNsensitive, False, NULL);
	XtSetValues(bCloseX, redwargs, 1);
	XtSetValues(bCreateX, greenwargs , 1);
	system ("./xdraw &");
	 
}
void OpenPCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	XtVaSetValues(bCloseP, XmNsensitive, True, NULL);
	XtVaSetValues(bCreateP, XmNsensitive, False, NULL);
	XtSetValues(bCloseP, redwargs, 1);
	XtSetValues(bCreateP, greenwargs, 1);
	system ("/usr/bin/python3 pdraw.py &");
}

void ModalBox()
{
	XmString xm_string;
	Arg args[1];
	Widget quitdlg;
	Widget remove;

	xm_string = XmStringCreateLocalized("Are you sure you want to quit?");
	XtSetArg(args[0], XmNmessageString, xm_string);
	quitdlg = XmCreateWarningDialog(quit, "quit", args,1);
	XtAddCallback(quitdlg, XmNokCallback, ConfirmQuitCallback, NULL);

	remove = XmMessageBoxGetChild(quitdlg, XmDIALOG_HELP_BUTTON);
	XtUnmanageChild(remove);
	XtManageChild(quitdlg);
}
void ConfirmQuitCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	if (childpid != 0)
	{
		
		kill(childpid, SIGTERM);
		waitpid(childpid, NULL, NULL);  
	}
	system ("pkill -9 xdraw");
	system ("pkill -9 python3");
	exit(0);
}

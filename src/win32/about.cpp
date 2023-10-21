// ---------------------------------------------------------------------------
//  M88 - PC-8801 emulator
//	Copyright (C) cisc 1998, 2000.
// ---------------------------------------------------------------------------
//	About Dialog Box for M88
// ---------------------------------------------------------------------------
//	$Id: about.cpp,v 1.28 2003/09/28 14:35:35 cisc Exp $

#include "headers.h"
#include "resource.h"
#include "about.h"
#include "version.h"
#include "filetest.h"

// ---------------------------------------------------------------------------
//	�\�z/����
//
M88About::M88About()
{
	SanityCheck(&crc);
}

// ---------------------------------------------------------------------------
//	�_�C�A���O�\��
//
void M88About::Show(HINSTANCE hinst, HWND hwndparent)
{
	DialogBoxParam(hinst, MAKEINTRESOURCE(IDD_ABOUT), 
				   hwndparent, DLGPROC((void*)DlgProcGate), (LPARAM)this); 
}

// ---------------------------------------------------------------------------
//	�_�C�A���O����
//
INT_PTR M88About::DlgProc(HWND hdlg, UINT msg, WPARAM wp, LPARAM lp)
{
	char buf[4096];
	
	switch (msg)
	{
	case WM_INITDIALOG:
		wsprintf(buf, "M88 for Win32 (rel " APP_VER_STRING ")\n"
					  "PC-8801 series emulator.\n"
					  "Copyright (C) 1998, 2003 cisc\n");
	
		SetDlgItemText(hdlg, IDC_ABOUT_TEXT, buf);

		wsprintf(buf, abouttext, crc);

		SetDlgItemText(hdlg, IDC_ABOUT_BOX, buf);

		SetFocus(GetDlgItem(hdlg, IDOK));
		return false;

	case WM_COMMAND:
		if (IDOK == LOWORD(wp))
		{
			EndDialog(hdlg, true);
			break;
		}
		return true;

	case WM_CLOSE:
		EndDialog(hdlg, false);
		return true;

	default:
		return false;
	}
	return false;
}

INT_PTR CALLBACK M88About::DlgProcGate
(HWND hwnd, UINT m, WPARAM w, LPARAM l)
{
	M88About* about = 0;
	if ( m == WM_INITDIALOG ) {
		about = reinterpret_cast<M88About*>(l);
		if (about) {
			::SetWindowLongPtr( hwnd, GWLP_USERDATA, (LONG_PTR)about );
		}
	} else {
		about = (M88About*)::GetWindowLongPtr( hwnd, GWLP_USERDATA );
	}

	if (about) {
		return about->DlgProc(hwnd, m, w, l);
	} else {
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
//	about �p�̃e�L�X�g
//
const char M88About::abouttext[] =
	"build date: 2023/10/18(%.8x)\r\n"
	"\r\n"
	"�v�]�E�o�O�񍐂Ȃǂ͈ȉ��̃y�[�W�ɂǂ���\r\n"
	"\r\n"
	"https://github.com/110-kenichi/m88\r\n"
	"\r\n"
	"�������� M88 �̃y�[�W\r\n"
	"https://github.com/rururutan/m88\r\n"
	"\r\n"
	"�I���W�i�� M88 �̃y�[�W\r\n"
	"\r\n"
	"http://www.retropc.net/cisc/m88/\r\n"
	"\r\n"
	"FM �������j�b�g�̍쐬�ɂ������ẮC\r\n"
	"�����B�V����� fm.c ���Q�l�ɂ����Ă��������܂����D\r\n"
	"\r\n"
	"N80/SR ���[�h�� arearea ���̃R�[�h�����Ɏ�������Ă��܂��D\r\n"
	;

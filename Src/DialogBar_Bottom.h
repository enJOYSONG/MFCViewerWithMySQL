#ifndef DIALOGBAR_BOTTOM_H
#define DIALOGBAR_BOTTOM_H
#include "afxwin.h"

// CDialogBar_Bottom dialog
class CRBX_Model;
class CDialogBar_Bottom: public CDialogBar
{
	DECLARE_DYNAMIC(CDialogBar_Bottom)

public:
	CDialogBar_Bottom();   // standard constructor
	virtual ~CDialogBar_Bottom();
	void SetModel(CRBX_Model* model);
	void UpdateModelInfo();
	void SetModelInfo();
	void DeleteModel();
// Dialog Data
	enum { IDD = IDD_DIALOGBAR_BOTTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CRBX_Model* m_Model;
	CEdit* m_EditDisplayName;
	CEdit* m_EditFileName;
	UINT m_TypeValue;
public:
	void SetType(UINT value);
	afx_msg void OnEnChangeDisname();
};
#endif
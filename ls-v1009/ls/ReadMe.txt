[ls.exe]
--2012.6.20 Wed --HYL--9106--
0. V:1.0.0.9 void CLSView::OnBmpSave() 
	
--2012.6.20 Wed --HYL--9106--
0. V:1.0.0.8   		m_SL_L.AddTail("  ***��������,����ʶ���������(http://www.dfguitar.com)��Ͱ�ӹ��ֶӹٷ���վ(http://www.tongzigu.com)***");

--2012.6.18 Mon --HYL--9106--
0. V:1.0.0.8
1. ��ӹ���: 1,2,3 ����¼�빦��.  ('f'+ 'i'('I'))



--2009.4.26 Sun --HYL--
0. V:1.0.0.7
1. ����BUG:
   BUG�����������ļ�ʱ,û�йرվ��ļ���
2. A: void CLSView::Xd_Init()
   A: void CLSDoc::DeleteContents() 
==================================================

--2009.4.25 Sat --HYL--
0. V:1.0.0.6
1. ����BUG:
   BUG�����������ļ�ʱ,û�йرվ��ļ���



--2009.4.23 Thu --HYL--
0. v:1.0.0.6
1. M:void CLSView::Xd_Lyr_Char(UINT nChar)
================================




--2009.4.22 Wed --HYL--
0. v:1.0.0.5
1. ����BUG��
   BUG����������������λ�ñ���html�ļ���
   M:

	char szTempFileName[1000];  //"base.htm"
	CString strBaseHtmFile = v_Get_Base_Htm_File();

	strcpy(szTempFileName,strBaseHtmFile.GetBuffer(strBaseHtmFile.GetLength()));
	TRACE("szTempFileName = %s",szTempFileName);
	
================================





2006.6.2

���� �׵�¼��: 'o','d','s'

�汾��Ϊ:V1.0.0.2

---2007.03.22------Xd----------
1. M: 
	base.htm
		xd_Lyr_Draw_A_Line
			var xl=x;// ԭ��Ϊ: var xl=0;

V1.0.0.2			

---2007.12.26 wed ---HYL--
1. V:1.0.0.3

--2008.1.17 Thu --HYL--
0. v:1.0.0.4
1. T: void CXdJPView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
	��ӡԤ��


================================
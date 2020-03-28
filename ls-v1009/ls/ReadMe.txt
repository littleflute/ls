[ls.exe]
--2012.6.20 Wed --HYL--9106--
0. V:1.0.0.9 void CLSView::OnBmpSave() 
	
--2012.6.20 Wed --HYL--9106--
0. V:1.0.0.8   		m_SL_L.AddTail("  ***更多乐谱,请访问东方吉他网(http://www.dfguitar.com)，桶子鼓乐队官方网站(http://www.tongzigu.com)***");

--2012.6.18 Mon --HYL--9106--
0. V:1.0.0.8
1. 添加功能: 1,2,3 房子录入功能.  ('f'+ 'i'('I'))



--2009.4.26 Sun --HYL--
0. V:1.0.0.7
1. 修正BUG:
   BUG描述：打开新文件时,没有关闭旧文件。
2. A: void CLSView::Xd_Init()
   A: void CLSDoc::DeleteContents() 
==================================================

--2009.4.25 Sat --HYL--
0. V:1.0.0.6
1. 修正BUG:
   BUG描述：打开新文件时,没有关闭旧文件。



--2009.4.23 Thu --HYL--
0. v:1.0.0.6
1. M:void CLSView::Xd_Lyr_Char(UINT nChar)
================================




--2009.4.22 Wed --HYL--
0. v:1.0.0.5
1. 修正BUG：
   BUG描述：不能在任意位置保存html文件。
   M:

	char szTempFileName[1000];  //"base.htm"
	CString strBaseHtmFile = v_Get_Base_Htm_File();

	strcpy(szTempFileName,strBaseHtmFile.GetBuffer(strBaseHtmFile.GetLength()));
	TRACE("szTempFileName = %s",szTempFileName);
	
================================





2006.6.2

增加 谱的录入: 'o','d','s'

版本升为:V1.0.0.2

---2007.03.22------Xd----------
1. M: 
	base.htm
		xd_Lyr_Draw_A_Line
			var xl=x;// 原来为: var xl=0;

V1.0.0.2			

---2007.12.26 wed ---HYL--
1. V:1.0.0.3

--2008.1.17 Thu --HYL--
0. v:1.0.0.4
1. T: void CXdJPView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
	打印预览


================================
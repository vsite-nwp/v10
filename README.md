#### vježba 10

Koristeći MFC napravite aplikaciju koja pristupa tablici User u Access bazi podataka preko ODBC-a.

![frame](/screenshot.jpg?raw=true)

Aplikacija štampa i jednostavni izvještaj za tablicu i mora podržavati preview ispisa. 

![preview](/preview.jpg?raw=true)


Uputstva:

*	napravite Access bazu sa jednom tablicom i tri polja
*	u Control Panel-u dodajte ODBC data source (System DSN) koji pokazuje na tu bazu
*	napravite pomoću AppWizard-a MFC aplikaciju:
  * Application type = "Single document"
  *	"Document/View architecture support" je uključen
  *	Database support = "Database view without file support"
  *	Data Source = kreirani data source, tablica = kreirana tablica
  *	"Printing and print preview" je uključen
  *	View klasa (RecView) je izvedena iz CRecordView 
*	na formu stavite 3 static-a,  2 edit-a i 1 checkbox
*	u RecView napravite DDX kontrola na članove klase izvedene iz CRecordSet

  ```
  DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
  DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
  DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
  ```

*	dodajte OnPrint() u RecView
*	u OnPrint() prođite kroz cijeli record set

  ```
  RecSet rs;
  rs.Open();
  while(!rs.IsEOF()){
    // draw current record
    rs.MoveNext();	
  }
  ```
*	širinu i visinu stranice papira možete saznati pomoću `GetDeviceCaps()` (HORZRES, VERTRES)
*	visinu reda teksta možete saznati pomoću `GetTextExtent()`

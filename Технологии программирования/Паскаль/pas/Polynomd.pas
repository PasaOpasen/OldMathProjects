USES
  crt;

TYPE
   Preal = ^real;
  Polynom = RECORD
    deg:WORD;
    coef:Preal;
  END;


{ᮧ����� �������� �⥯��� n}
FUNCTION CreatePolynom (n:WORD): Polynom;
VAR
  p:Polynom;
BEGIN
  new(p.coef);
  p.deg := n;
  GetMem(p.coef,(n+1)*sizeOf(real));
  CreatePolynom:=p;
END;


{���㫥��� ��������}
{PROCEDURE KillPolynom (VAR p:Polynom);
BEGIN
  FreeMem(p.coef,(p.deg+1)*sizeOf(real));
  dispose(p);
  p:= NULL;
END;  }


{���⨥ ���祭�� k-�� �����樥��}
FUNCTION GetCoef(p:Polynom; k:WORD):REAL;
VAR
  ptr:Preal;
BEGIN
  ptr:=p.coef;
  inc(ptr,k);
  GetCoef:=ptr^;
END;

{��᢮���� k-�� �����樥��� ���祭�� a}
PROCEDURE SetCoef(p:Polynom; k:WORD; a:REAL);
VAR
  ptr:Preal;
BEGIN
  ptr:=p.coef;
  inc(ptr,k);
  ptr^:=a;

  //WriteLn(GetCoef(p,k));
END;

{�㬬� ���������}
{FUNCTION SumPolynom (p,q: Polynom): Polynom;
VAR
  f:Polynom;
  i: WORD;
BEGIN
  if p^.deg>q^.deg THEN f:=CreatePolynom(p^.deg)
  ELSE f:=CreatePolynom(q^.deg);

  IF p^.deg=q^.deg THEN
    FOR i:=0 TO p^.deg DO SetCoef(f,i,GetCoef(p,i)+GetCoef(q,i))
  ELSE IF p^.deg<q^.deg THEN
    BEGIN
      FOR i:=q^.deg DOWNTO p^.deg DO SetCoef(f,i,GetCoef(p,i)+GetCoef(q,i));
      FOR i:=p^.deg DOWNTO 0 DO SetCoef(f,i,GetCoef(q,i));
    END
  ELSE IF q^.deg<p^.deg THEN
    BEGIN
      FOR i:=p^.deg DOWNTO q^.deg DO SetCoef(f,i,GetCoef(p,i)+GetCoef(q,i));
      FOR i:=q^.deg DOWNTO 0 DO SetCoef(f,i,GetCoef(p,i));
    END;

  SumPolynom:=f;

  Write('(',GetCoef(f,0):3:4,') + ');
  FOR i:=1 TO (f^.deg-1) DO Write('(',GetCoef(f,i):3:4,')x^',i,' + ');
  Write('(',GetCoef(f,f^.deg):3:4,')x^',i+1);WriteLn();
END;}

{ࠧ����� ���������}
{FUNCTION DifPolynom (p,q: Polynom): Polynom;
VAR
  f:Polynom;
  i: WORD;
BEGIN
  if p^.deg>q^.deg THEN f:=CreatePolynom(p^.deg)
  ELSE f:=CreatePolynom(q^.deg);

  IF p^.deg=q^.deg THEN
    FOR i:=0 TO p^.deg DO SetCoef(f,i,GetCoef(p,i)-GetCoef(q,i))
  ELSE IF p^.deg<q^.deg THEN
    BEGIN
      FOR i:=q^.deg DOWNTO p^.deg DO SetCoef(f,i,GetCoef(p,i)-GetCoef(q,i));
      FOR i:=p^.deg DOWNTO 0 DO SetCoef(f,i,-GetCoef(q,i));
    END
  ELSE IF q^.deg<p^.deg THEN
    BEGIN
      FOR i:=p^.deg DOWNTO q^.deg DO SetCoef(f,i,GetCoef(p,i)-GetCoef(q,i));
      FOR i:=q^.deg DOWNTO 0 DO SetCoef(f,i,GetCoef(p,i));
    END;

  DifPolynom:=f;
  Write('(',GetCoef(f,0):3:4,') + ');
  FOR i:=1 TO (f^.deg-1) DO Write('(',GetCoef(f,i):3:4,')x^',i,' + ');
  Write('(',GetCoef(f,f^.deg):3:4,')x^',i+1); WriteLn();
END;}

{�ந�������� ���������}
{FUNCTION PowerPolynom (p,q: Polynom): Polynom;
VAR
  f:Polynom;
  s:REAL;
  i,j: WORD;
BEGIN
  f:=CreatePolynom(q^.deg+p^.deg);


  FOR i:=0 DOWNTO p^.deg+q^.deg DO
  BEGIN
    s:=0;
    FOR j:=0 TO i DO s:= s+GetCoef(p,j)*GetCoef(q,i-j);
    SetCoef(f,i,s)
  END;

  PowerPolynom:=f;

  Write('(',GetCoef(f,0):3:4,') + ');
  FOR i:=1 TO (f^.deg-1) DO Write('(',GetCoef(f,i):3:4,')x^',i,' + ');
  Write('(',GetCoef(f,f^.deg):3:4,')x^',i+1); WriteLn();
  END;
END;}

{���� �������� (�ᯮ����⥫쭠�)}
PROCEDURE InPutP(a:Polynom);
VAR
  i,n:WORD;
  b:REAL;
BEGIN
  WriteLn();
  WriteLn('input n (degree of polynom)');
  ReadLn(n); a:=CreatePolynom(n);
  WriteLn('input coef (',n+1,' koeffitsents on increase of degree)');
  FOR i:=0 TO n DO
  BEGIN
    Read(b);
    SetCoef(a,i,b);
  END;

   Write('(',GetCoef(a,0):3:4,') + ');
  FOR i:=1 TO (a.deg-1) DO Write('(',GetCoef(a,i):3:4,')x^',i,' + ');
  Write('(',GetCoef(a,a.deg):3:4,')x^',i+1);WriteLn();
END;

{�뢮� �������� (�ᯮ����⥫쭠�)}
PROCEDURE OutPutP(a:Polynom);
VAR
  i: WORD;
BEGIN
  WriteLn();
  Write('(',GetCoef(a,0):3:4,') + ');
  FOR i:=1 TO (a.deg-1) DO Write('(',GetCoef(a,i):3:4,')x^',i,' + ');
  Write('(',GetCoef(a,a.deg):3:4,')x^',i+1);WriteLn();
END;


VAR
 a,b:Polynom;
BEGIN
 ClrScr;

 InPutP(a);//OutPutP(a);
 //InPutP(b);//OutPutP(b);

 {OutPutP(SumPolynom(a,b));
 OutPutP(DifPolynom(a,b));
 OutPutP(PowerPolynom(a,b));}

  //WriteLn(GetCoef(a,0));  WriteLn(GetCoef(a,1));

  WriteLn(a.deg);

 ReadKey;
END.




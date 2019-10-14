USES
  crt;

TYPE
   Polynom = ^bPolynom;
  bPolynom = RECORD
    deg:WORD;
    coef:PDouble;
  END;


{ᮧ����� �������� �⥯��� n}
FUNCTION CreatePolynom (n:WORD): Polynom;
VAR
  p:Polynom;
BEGIN
  new(p);
  p^.deg := n;
  GetMem(p^.coef,(n+1)*sizeOf(real));
  CreatePolynom:=p;
END;


{���㫥��� ��������}
{PROCEDURE KillPolynom (VAR p:Polynom);
BEGIN
  FreeMem(p^.coef,(p^.deg+1)*sizeOf(real));
  dispose(p);
  p:= NULL;
END;  }

{�㭪��, ���ன ��ᢠ������� ���祭�� ��������}
{FUNCTION Reminder (rem: Polynom): Polynom;
BEGIN
  Reminder:=rem;
END;}

{��᢮���� k-�� �����樥��� ���祭�� a}
PROCEDURE SetCoef(p:Polynom; k:WORD; a:REAL);
VAR
  ptr:PDouble;
BEGIN
  ptr:=p^.coef;
  inc(ptr,k);
  ptr^:=a;
END;

{���⨥ ���祭�� k-�� �����樥��}
FUNCTION GetCoef(p:Polynom; k:WORD):REAL;
VAR
  ptr:PDouble;
BEGIN
  ptr:=p^.coef;
  inc(ptr,k);
  GetCoef:=ptr^;
END;

{�㬬� ���������}
FUNCTION SumPolynom (p,q: Polynom): Polynom;
VAR
  f:Polynom;
  i: WORD;
BEGIN
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
END;

{ࠧ����� ���������}
FUNCTION DifPolynom (p,q: Polynom): Polynom;
VAR
  f:Polynom;
  i: WORD;
BEGIN
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
END;

{�ந�������� ���������}
FUNCTION PowerPolynom (p,q: Polynom): Polynom;
VAR
  f:Polynom;
  s:REAL;
  i,j: WORD;
BEGIN
  FOR i:=0 DOWNTO p^.deg+q^.deg DO
  BEGIN
    s:=0;
    FOR j:=0 TO i DO s:= s+GetCoef(p,j)*GetCoef(q,i-j);
    SetCoef(f,i,s)
  END;

  PowerPolynom:=f;
END;

{���� �������� (�ᯮ����⥫쭠�)}
PROCEDURE InPutP(a:Polynom);
VAR
  i,n:WORD;
  b:REAL;
BEGIN
  WriteLn();
  WriteLn('input n');
  ReadLn(n); a:=CreatePolynom(n);
  WriteLn('input coef...');
  FOR i:=0 TO n DO
  BEGIN
    Read(b);
    SetCoef(a,i,b);
  END;
END;

{�뢮� �������� (�ᯮ����⥫쭠�)}
PROCEDURE OutPutP(a:Polynom);
VAR
  i: WORD;
BEGIN
  WriteLn();
  FOR i:=0 TO (a^.deg-1) DO Write('(',GetCoef(a,i),')x^',i,' + ');
  Write('(',GetCoef(a,a^.deg),')x^',i);
END;


VAR
 a,b,f:Polynom;
BEGIN
 ClrScr;

 InPutP(a);{OutPutP(a);
 InPutP(b);OutPutP(b);

 OutPutP(SumPolynom(a,b));
 OutPutP(DifPolynom(a,b));
 OutPutP(PowerPolynom(a,b)); }
 Write(GetCoef(a,0));

 ReadKey;
END.




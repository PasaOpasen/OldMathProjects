USES
  Crt;

TYPE
Line = RECORD
  A, B, C: REAL;
END;

Point = ARRAY [1..2] OF REAL;
Vector = ARRAY [1..2] OF REAL;
Circle = RECORD
  center: Point;
  radius: REAL;
END;

VAR eps: REAL;


PROCEDURE INTERSECTION(P: Point; VAR a, b: Line);
VAR
s1, S2, S: REAL;
BEGIN

  S := a.A*b.B - a.B*b.A;
  IF s < eps THEN
    Writeln('���� �� ����� �窨 ����祭��')
  ELSE
  BEGIN
    s1 := (-a.C*b.B + a.B*b.C)/s;
    s2 := (-a.A*b.C + b.A*a.C)/s;
    P[1] := s1;
    P[2] := s2;
    WriteLn('���न���� �窨 ����祭��  ','(',s1:5:2,',',s2:5:2,')');
  END;
END;


PROCEDURE PositionOfPoints(P, F: Point; a: Line);
VAR
s1, s2, s,ab: REAL;
b:Line;
G:Point;
BEGIN
  {�஢������ ��אַ� �१ �窨 P � F}
  b.A := F[2] - P[2];
  b.B := P[1] - F[1];
  b.C := F[1]*P[2]-P[1]*F[2];


  S := a.A*b.B - a.B*b.A;

  IF abs(s) < eps THEN
    IF abs(a.C - b.C) < eps THEN
      Writeln('�窨 ����� �� ������ ��אַ�')
    ELSE
      WriteLn('�窨 ����� �� ���� ��஭� �� ��אַ�')
  ELSE
  BEGIN
    s1 := (-a.C*b.B + a.B*b.C)/s;
    s2 := (-a.A*b.C + b.A*a.C)/s;
    G[1] := s1;
    G[2] := s2;

    s := (sqrt(sqr(P[1]-s1)+sqr(P[2]-s2)));
    ab := (sqrt(sqr(F[1]-s1)+sqr(F[2]-s2)));

    IF  s < eps THEN
      WriteLn('���� �� �祪 ����� �� ��אַ�')
    ELSE IF ab < eps THEN
      WriteLn('���� �� �祪 ����� �� ��אַ�')
    ELSE
      BEGIN
        s := s + ab;
        ab :=  sqrt(sqr(P[1]-F[1])+sqr(P[2]-F[2]));
        IF abs(s-ab) < eps THEN
          WriteLn('�窨 ����� �� ࠧ�� ��஭� �� ��אַ�')
        ELSE
          WriteLn('�窨 ����� �� ���� ��஭� �� ��אַ�')
      END;
  END;
END;

FUNCTION PositionPoints(P, F: Point; a: Line):BOOLEAN;
VAR
s1, s2, s,ab: REAL;
b:Line;
G:Point;
BEGIN
  {�஢������ ��אַ� �१ �窨 P � F}
  b.A := F[2] - P[2];
  b.B := P[1] - F[1];
  b.C := F[1]*P[2]-P[1]*F[2];


  S := a.A*b.B - a.B*b.A;

  IF abs(s) < eps THEN
    IF abs(a.C - b.C) < eps THEN
      {Writeln('�窨 ����� �� ������ ��אַ�')} PositionPoints := FALSE
    ELSE
      {WriteLn('�窨 ����� �� ���� ��஭� �� ��אַ�')} PositionPoints := FALSE
  ELSE
  BEGIN
    s1 := (-a.C*b.B + a.B*b.C)/s;
    s2 := (-a.A*b.C + b.A*a.C)/s;
    G[1] := s1;
    G[2] := s2;

    s := (sqrt(sqr(P[1]-s1)+sqr(P[2]-s2)));
    ab := (sqrt(sqr(F[1]-s1)+sqr(F[2]-s2)));

    IF  s < eps THEN
      {WriteLn('���� �� �祪 ����� �� ��אַ�')} PositionPoints := FALSE
    ELSE IF ab < eps THEN
      {WriteLn('���� �� �祪 ����� �� ��אַ�')} PositionPoints := FALSE
    ELSE
      BEGIN
        s := s + ab;
        ab :=  sqrt(sqr(P[1]-F[1])+sqr(P[2]-F[2]));
        IF abs(s-ab) < eps THEN
          {WriteLn('�窨 ����� �� ࠧ�� ��஭� �� ��אַ�')} PositionPoints := TRUE
        ELSE
          {WriteLn('�窨 ����� �� ���� ��஭� �� ��אַ�')} PositionPoints := FALSE
      END;
  END;
Writeln(PositionPoints);
END;

PROCEDURE TANGENT(v: Line; VAR ASD:Circle; a: Vector);
VAR
q, w, e: REAL;
f: Point;
BEGIN
q := sqrt(sqr(a[1])+sqr(a[2]));
a[1] := a[1] / q; a[2] := a[2] / q;
a[1] := a[1] * ASD.radius; a[2] := a[2] * ASD.radius;

f[1] := ASD.center[1] + a[1]; f[2] := ASD.center[2] + a[2];

v.A := a[1]; v.B := a[2]; v.C := -(v.A*f[1] + v.B*f[2]);
{WriteLn('��ﬠ� ����� �ࠢ�����: ',v.A:5:2,'x + ',v.B:5:2,'y + ',v.C:5:2,' = 0');}
END;


VAR
  a,b,c,d:Line;
  P,F,Q:Point;
  e:Vector;
  ASD:Circle;
BEGIN
  eps := 0.0001;
  ClrScr;

  WriteLn();
  a.A:=0;a.B:=1;a.C:=0;
  b.A:=0;b.B:=0;b.C:=-3;
  P[1]:=0;P[2]:=0;

  INTERSECTION(P,a,b);

  WriteLn();
  Q[1]:=0;Q[2]:=0;
  F[1]:=1;F[2]:=0;
  c.A:=0;c.B:=1;c.C:=0;
  PositionOfPoints(Q,F,c);
  PositionPoints(Q,F,c);

  WriteLn();
  d.A:=0;d.B:=1;d.C:=0;
  ASD.center[1]:=0;
  ASD.center[2]:=0;
  ASD.radius:=1;
  e[1]:=0; e[2]:= -5;
  TANGENT(d,ASD,e);
  WriteLn('��ﬠ� ����� �ࠢ�����: ',d.A:5:2,'x + ',d.B:5:2,'y + ',d.C:5:2,' = 0');


ReadKey;
end.
















USES
Crt;

CONST
  n = 5;
  m = 4;
VAR
  a:ARRAY [1..n,1..m] OF integer;
  i, k, p, b, j, c, sum, min, max, mi, ma, x, u:integer;

BEGIN
  b := 0;
  c := 0;

a[1,1] := 7;  a[2,1] := -7;  a[3,1] := 5;  a[4,1] := -3;  a[5,1] := 1;
a[1,2] := 1;  a[2,2] := -8;  a[3,2] := 5;  a[4,2] := -3;  a[5,2] := 0;
a[1,3] := 6;  a[2,3] := -8;  a[3,3] := 15;  a[4,3] := -100;  a[5,3] := 278;
a[1,4] := 3;  a[2,4] := 8;  a[3,4] := 5;  a[4,4] := -10;  a[5,4] := 28;

WriteLn();
WriteLn();

  FOR j:=1 TO m DO
  BEGIN
    FOR i:=1 TO n DO
    BEGIN
      IF a[i,j] < 0 THEN b := a[i,j];
      IF a[i,j] > 0 THEN c := a[i,j];
    END;
  END;
  k := a[1,j];
  p := a[n,j];

  FOR j:=1 TO m DO
  BEGIN
    FOR i:=1 TO n DO
    BEGIN
      IF a[i,j] > k THEN k := a[i,j];
      IF a[i,j] < p THEN p := a[i,j];
    END;
  END;
  WriteLn('maximal element is ', k);
  WriteLn('minimal element is ', p);


  IF b = 0 THEN WriteLn('maxinal negative element is not exist')
  ELSE
  BEGIN
    BEGIN
    FOR j:=1 TO m DO
      BEGIN
        FOR i:=1 TO n DO
        IF (a[i,j] > b) AND (a[i,j] < 0) THEN b := a[i,j];
      END;
    END;
  WriteLn('maxinal negative element is ', b);
  END;

  IF c = 0 THEN WriteLn('minimal positive element is not exist')
  ELSE
  BEGIN
    FOR j:=1 TO m DO
    BEGIN
      BEGIN
      FOR i := 1 TO n DO
      IF (a[i,j] < c) AND (a[i,j] > 0) THEN c := a[i,j];
      END;
    END;
  WriteLn('minimal positive element is ', c);
  END;


    FOR i:=1 TO n DO
        sum := sum + a[i,1];
        min := sum;
        max := sum;
        ma := 1;
        mi := 1;

   BEGIN
    FOR j:=2 TO m DO
      BEGIN
        sum := 0;
        FOR i:=1 TO n DO
        sum := sum + a[i,j];
        IF sum < min THEN
        BEGIN
          min := sum;
          mi := j;
        END;
        IF sum > max THEN
        BEGIN
          max := sum;
          ma := j;
        END;
      END;
   END;
   WriteLn('minimal sum is ',min,', number of the string is ',mi);
   WriteLn('maximal sum is ',max,', number of the string is ',ma);

   FOR j := 1 TO m DO
   BEGIN
     x := 1;
     u := 0;
     FOR i := n DOWNTO 1 DO
     BEGIN
     IF a[i,j] mod 2 = 0 THEN
       BEGIN
       x := a[i,j];
       u := 1;
       END;
     END;
     IF u = 1 THEN
     WriteLn ('the last even elememt in ',j,' string is ', x,';')
     ELSE WriteLn ('even elements does not exist in the string ', j,';');
   END;

ReadKey;
END.

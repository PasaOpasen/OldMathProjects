/* Программа: Служащие */
/* Назначение: 
Демонстрация использования селектирующих правил на основе ОПН-метода 
(ОНП = откат после неудачи)*/

domains
  name, sex, department = symbol %имя, пол, место работы
  pay_rate = real %ставка оплаты труда

predicates
  employee(name,sex,department,pay_rate) % работник
  show_employees
  show_employees_male


clauses
%используется очень мало записей, чтобы ответы поместились в окошко Turbo Prolog 
  employee("Presley Perry","Male","ACCT",133.50).
  employee("Noelle Carter","Female","DATA",145.00).
  employee("Kye Coleman","Male","DATA",346.00).
  employee("Sheila Burton","Female","ADVE",235.00).


  /* Правило для генерации списка служащих любого пола */
  show_employees :-
    employee(Name, Sex, Dept, Pay_rate),
    write(Name," Sex: ",Sex," Department: ", Dept, " Pay by hour($): ", Pay_rate),
    nl,nl, % nl = переход на следующую строку
    fail.

  /* Правило для генерации списка служащих мужского пола */
  show_employees_male :-
    employee(Name, "Male", Dept, Pay_rate),
    write(Name," Department: ", Dept, " Pay($): ", Pay_rate),
    nl,nl,
    fail.



goal
 write("Employees with their pay rate:"),
 nl, nl,
 show_employees,
 nl, nl,
 write("Employees with their pay rate (only men):"),
 nl, nl,
 show_employees_male.

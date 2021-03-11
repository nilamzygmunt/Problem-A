import java.util.Iterator;
import Iterators.*;

public class Main
{
    public static void main(String[] args)
    {
        Student[] s = new Student[5];
        s[0] = new Student(1234, "Kowalski", "Jan", 5);
        s[1] = new Student(1235, "Kowalska", "Ala", 4);
        s[2] = new Student(1236, "Nowak", "Adam", 2);
        s[3] = new Student(1237, "Kowalski", "John",3 );
        s[4] = new Student(1238, "Nowak", "Anna", 4);

        Student stud = new Student();
        //wyswietl
        Iterator<Student> iterStudent = new ArrayIterator<Student>(s);
        stud.wyswietl(iterStudent);

        //zmien ocene
        Iterator<Student> iterStudent2 = new ArrayIterator<Student>(s);
        stud.zmienOcene(1235, 5, iterStudent2);

        //srednia
        class StudentPoz implements Predicate
        {
            @Override
            public boolean accept(Object arg)
            {
                Student s = (Student) arg;
                return s.getOcena()>=3;
            }
        }
        Predicate StudPoz = new StudentPoz();
        Iterator<Student> iterStudent3 = new ArrayIterator<Student>(s);
        Iterator<Student> FilterIter = new FilterIterator<Student>(iterStudent3, StudPoz);
        stud.srednia(FilterIter);

        //niezaliczony
        class StudentNeg implements Predicate
        {
            @Override
            public boolean accept(Object arg)
            {
                Student s = (Student) arg;
                return s.getOcena()<3;
            }
        }
        Predicate StudNeg = new StudentNeg();
        Iterator<Student> iterStudent4= new ArrayIterator<Student>(s);
        Iterator<Student> FilterIter2 = new FilterIterator<Student>(iterStudent4, StudPoz);
        stud.nieZaliczone(FilterIter2);
    }
}

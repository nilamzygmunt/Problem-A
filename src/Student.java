
import java.util.Iterator;

public class Student
{
    private int numer_indeksu;
    private String nazwisko;
    private String imie;
    private int ocena;

    public Student()
    {
        numer_indeksu = 0;
        nazwisko = "";
        imie = "";
        ocena = 0;
    }

    public Student(int numer_indeksu, String nazwisko, String imie, int ocena)
    {
        this.numer_indeksu = numer_indeksu;
        this.nazwisko = nazwisko;
        this.imie = imie;
        this.ocena = ocena;
    }

    public int getNumer_indeksu()
    {
        return numer_indeksu;
    }

    public String getNazwisko()
    {
        return nazwisko;
    }

    public String getImie()
    {
        return imie;
    }

    public int getOcena()
    {
        return ocena;
    }

    public void setNumer_indeksu(int numer_indeksu)
    {
        this.numer_indeksu = numer_indeksu;
    }

    public void setNazwisko(String nazwisko)
    {
        this.nazwisko = nazwisko;
    }

    public void setImie(String imie)
    {
        this.imie = imie;
    }

    public void setOcena(int ocena)
    {
        this.ocena = ocena;
    }

    /*public void wyswietl()
    {
        System.out.println("numer indeksu: "+ getNumer_indeksu()+"\timie: "+getImie()+"\tnazwisko:"+getNazwisko()+"\tocena: "+getOcena());
    }*/

    public void wyswietl(Iterator iter)
    {
        while (iter.hasNext())
        {
           Student student = (Student) iter.next();
            System.out.println("numer indeksu: "+ student.getNumer_indeksu() +"\timie: "+ student.getImie()+"\tnazwisko:"+student.getNazwisko()+"\tocena: "+student.getOcena());
        }

        System.out.println();
    }

    public void zmienOcene(int numer_indeksu, int ocena, Iterator iter)
    {
        boolean znaleziono = false;
        while(iter.hasNext())
        {
            Student student = (Student) iter.next();
            if (student.getNumer_indeksu() == numer_indeksu)
            {
                System.out.print("\nZmieniam ocene studenta " + student.getImie() + " z " + student.getOcena() + " na ");
                student.setOcena(ocena);
                znaleziono = true;
                System.out.println(student.getOcena());
            }
        }

    }

    public void srednia(Iterator iter)
    {
        double srednia=0;
        double ilosc=0;
        System.out.println();
        System.out.print("srednia: ");
        while (iter.hasNext())
        {
            Student student = (Student) iter.next();
            srednia+=student.getOcena();
            ilosc++;
        }
        System.out.println(srednia/ilosc);

    }
    public static void nieZaliczone(Iterator iter)
    {
        System.out.println("\nNie zaliczyli: ");
        while (iter.hasNext())
        {
            Student student = (Student) iter.next();

            System.out.println("numer indeksu: " + student.getNumer_indeksu() + "\timie: " + student.getImie() + "\tnazwisko:" + student.getNazwisko() + "\tocena: " + student.getOcena());
        }
        System.out.println();
    }
}
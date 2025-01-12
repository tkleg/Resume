
import java.io.*;
public class testStream
{
      public static void main(String[] args)
      {
        String fileName = "object.out";
        Object a = null;
        try {
          FileInputStream fileIn =
            new FileInputStream(fileName);
          ObjectInputStream in =
            new ObjectInputStream(fileIn);
          a = in.readObject();
          in.close();
        }
        catch (IOException e) {
          System.out.println(e.getMessage());
        }
        catch (ClassNotFoundException e)
        {
          System.out.println(e.getMessage());
        }

      }
}

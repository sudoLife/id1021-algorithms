public class test {
   public static void main(String[] args) 
   {
    String testStr = "öäÅ";

    for (int i = 0; i < testStr.length(); i++)
    {
        int test = testStr.charAt(i);
        System.out.println(test);
    }
   }
}

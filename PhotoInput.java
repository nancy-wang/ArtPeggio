import java.io.File;
import java.io.IOException;
import java.awt.image.BufferedImage;
import java.awt.image.Raster;
import java.awt.image.WritableRaster;
import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.metadata.*;
import javax.imageio.stream.*;
import java.awt.image.DataBufferByte;
import java.util.Iterator;
import javax.sound.midi.*;
import javax.sound.sampled.AudioPermission;

public class PhotoInput {
   public static void main(String[] args) {
      //adds permission to play the music
      AudioPermission permission = new AudioPermission("permission", "play");
      //store filepath to photo
      String filepath = "./drawables/ex01.jpg";
      
      //the number of divisions to make (a little bit buggy, actually divides into 21?)
      int numSamples = 20;
      //array to store all the individual RGB values.
      //R = 0
      //G = 1
      //B = 2
      int[][] rgb = new int[(numSamples + 1) * (numSamples + 1)][3];
      //The key is for future, if we use chords
      //loadPhoto puts the data from the filepath/image into the rgb array
      int key = loadPhoto(filepath, rgb, numSamples);
      //Play the music
      playMusic(rgb, key);
   }
   
   //load the photo from the path into the rgb arrays
   public static int loadPhoto(String filepath, int[][] rgb, int numSamples) {
      BufferedImage image = null;
      File f = null;
      
      //create new file, and read the file using imageio
      try {
         f = new File(filepath);
         image = ImageIO.read(f);
      } 
      catch (IOException e) {
         System.out.println(e);
      } 
      catch (Exception e) {
         System.out.println(e);
      }
        
   
      //array for pixels, not sure how this works tbh
      byte[] pixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
      //image width and height
      int width = image.getWidth();
      int height = image.getHeight();
      //rgbTot calculates total, in order to do mean calculation later
      int[] rgbTot = new int[3];
      //volume to play the notes at
      int vol = 100;
      //total number of pixels grabbed so far
      int pixelsSampled = 0; 
   
      //go through the height/rows, moving each time by height/numSamples  
      for (int y = 0; y < height; y += Math.ceil(height/numSamples)) {
         //gp through the width/columns
         for (int x = 0; x < width; x += Math.ceil(width/numSamples)) {
            //get the entire color array, at x, y, which contains RGB
            int clr = image.getRGB(x,y);
            //grabs the bytes where the ffs are, and shifts it to the uttermost
            //right
            rgbTot[0] += (int) ((clr & 0x00ff0000) >> 16);
            rgbTot[1] += (int) ((clr & 0x0000ff00) >> 8);
            rgbTot[2] += (int) clr & 0x000000ff;
            
            //no cast bc I don't think it matters
            //grabs each r, g, and b value, respectively
            rgb[pixelsSampled][0] = ((clr & 0x00ff0000) >> 16);
            rgb[pixelsSampled][1] = ((clr & 0x0000ff00) >> 8);
            rgb[pixelsSampled][2]= (clr & 0x000000ff);
            
            //print out the totals and | the actual values
            System.out.printf("Loop: %d Rt: %5d Gt: %5d Bt: %5d | ", pixelsSampled,
                    (rgbTot[0]), (rgbTot[1]), (rgbTot[2]));
            System.out.printf("Rv: %3d Gv: %3d Bv: %3d\n", 
                    (rgb[pixelsSampled][0]/2), (rgb[pixelsSampled][1]/2), 
                    (rgb[pixelsSampled][2]/2));
            //keep track of how many pixels sampled
            pixelsSampled++;
         }  
         
      }
      //make sure that pixels exist
      assert pixelsSampled != 0;
      //calculate averages
      rgbTot[0] = rgbTot[0]/pixelsSampled;
      rgbTot[1] = rgbTot[1]/pixelsSampled;
      rgbTot[2] = rgbTot[2]/pixelsSampled;
      //average the three totals to get an ultimate mean
      int total_mean = (rgbTot[0] + rgbTot[1] + rgbTot[2]) / 3;
      return total_mean;
   }

   public static void playMusic(int rgb[][], int key) {
   /* Meant for the chords but was never implemented
      System.out.println(key);
        //  I:  0 4 7
        //  V: -1 2 7
        // VI:  0 4 9
        // IV:  0 5 9
      final int ZERO = key;
      final int FOUR = key + 4;
      final int SEVEN = key + 7;
      final int NEG_ONE = key - 1;
      final int TWO = key + 2;
      final int NINE = key + 9;
      final int FIVE = key + 5;*/
      final int QUARTER = 100;
      
        
        //create Synthesizer 
      Synthesizer midiSynth = null;
      try { 
         //get and open synthesizer
         midiSynth = MidiSystem.getSynthesizer();
         midiSynth.open();
      } 
      catch (Exception e) {
         System.out.println(e);
      }
        //get instruments and channels, load the default instrument
      Instrument[] instr = midiSynth.getDefaultSoundbank().getInstruments();
      MidiChannel[] mChannels = midiSynth.getChannels();
      midiSynth.loadInstrument(instr[0]);
        
      //volume of the melody and chords
      int vol = 100;
      int volChord = 50;
   
        //notes since last chord;
        //int chordCounter = 1;
      for (int r = 0; r < rgb.length; r++) {
         /* Chord code
         switch (chordCounter) {
            case 1:
                        //turn off all previous notes
               mChannels[1].noteOn(ZERO, volChord);
               mChannels[1].noteOn(FOUR, volChord);
               mChannels[1].noteOn(SEVEN, volChord);
               chordCounter++;
               break;
            case 2:
                        
               mChannels[1].noteOn(NEG_ONE, volChord);
               mChannels[1].noteOn(TWO, volChord);
               mChannels[1].noteOn(SEVEN, volChord);
               chordCounter++;
               break;
            case 3:
                        
               mChannels[1].noteOn(ZERO, volChord);
               mChannels[1].noteOn(FOUR, volChord);
               mChannels[1].noteOn(NINE, volChord);
               chordCounter++;
               break;
                    
            case 4:
            
               mChannels[1].noteOn(ZERO, volChord);
               mChannels[1].noteOn(FIVE, volChord);
               mChannels[1].noteOn(NINE, volChord);
               chordCounter++;
               break;
            default:
               ;
         }*/
                
         System.out.println("Now for the notes");
         
         for (int c = 0; c < 3; c++) {
            //play the note at each index
            mChannels[0].noteOn(rgb[r][c]/2, vol);
            System.out.println(rgb[r][c]/2 + "r: " + r);
            try {
               //quarter is how long a quarter note is
               Thread.sleep(QUARTER);
            } 
            catch (InterruptedException e) {
            }
         }
         
         //turn the notes off after you play them
         for (int c = 0; c < 3; c++) {
            mChannels[0].noteOff(rgb[r][c]/2);
         }
         
         /*
         mChannels[0].noteOn(rgb[r][0]/2, vol);
         try {
            Thread.sleep(QUARTER);
         } 
         catch (InterruptedException e) {
            mChannels[0].noteOff(rgb[r][0]/2);
         }
      
                //SECOND NOTE
         mChannels[0].noteOn(rgb[r][1]/2, vol);
         try {
            Thread.sleep(QUARTER);
         } 
         catch (InterruptedException e) {
            mChannels[0].noteOff(rgb[r][1]/2);
         }
                
                //THIRD NOTE
         mChannels[0].noteOn(rgb[r][2]/2, vol);
         try {
            Thread.sleep(QUARTER);
         } 
         catch (InterruptedException e) {
            mChannels[0].noteOff(rgb[r][2]/2);
         }
      
                //FIRST NOTE
         mChannels[0].noteOn(rgb[r][0]/2, vol);
         try {
            Thread.sleep(QUARTER);
         } 
         catch (InterruptedException e) {
            mChannels[0].noteOff(rgb[r][0]/2);
         }*/
      
         /*       //turn off all previous notes
         switch (chordCounter) {
            case 1:
               mChannels[0].noteOff(ZERO);
               mChannels[0].noteOff(FOUR);
               mChannels[0].noteOff(SEVEN);
               chordCounter++;
               break;
            case 2:
                        
               mChannels[0].noteOff(NEG_ONE);
               mChannels[0].noteOff(TWO);
               mChannels[0].noteOff(SEVEN);
               chordCounter++;
               break;
            case 3:
                        
               mChannels[0].noteOff(ZERO);
               mChannels[0].noteOff(FOUR);
               mChannels[0].noteOff(NINE);
               chordCounter++;
               break;
                    
            case 4:
            
               mChannels[0].noteOff(ZERO);
               mChannels[0].noteOff(FIVE);
               mChannels[0].noteOff(NINE);
               chordCounter++;
               break;
            default:
               ;
         }
                //rotate the counter: chordCounter == 4 ? = 1 : ++
         if (chordCounter == 4) {
            chordCounter = 1;
         }
         else {
            chordCounter++;
         }*/
      
      }
   }
}

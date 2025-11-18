import sys
import os 
import win32com.client

def convert(input_file, output_file):
    """Convert PowerPoint to PDF"""
    powerpoint = None
    presentation = None
    try:
        # Use absolute paths
        input_file = os.path.abspath(input_file)
        output_file = os.path.abspath(output_file)
        
        # Create PowerPoint application instance
        powerpoint = win32com.client.DispatchEx("Powerpoint.Application")
        powerpoint.Visible = 1  

        # Open presentation with full path
        presentation = powerpoint.Presentations.Open(input_file, WithWindow=False)
        
        # Save as PDF (format type 32)
        presentation.SaveAs(output_file, 32)
        
        return True
    except Exception as e:
        return str(e)
    finally:
        # Clean up - close presentation and quit PowerPoint
        try:
            if presentation:
                presentation.Close()
            if powerpoint:
                powerpoint.Quit()
        except:
            pass
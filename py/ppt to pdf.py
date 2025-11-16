import sys
import os 
import comtypes.client

def convert(ppt_path, pdf_path):
    pdf_path = "C:\Users\kim\Desktop\Perosnal Project"

    powerpoint = comtypes.client.CreateObject("Powerpoint.Application")
    powerpoint.Visible = False
    slides = powerpoint.Presentations.Open(ppt_path)

    file_name = os.path.splitext(os.path.basename(ppt_path))[0]
    output_file_path = os.path.join(pdf_path, file_name + ".pdf")
    
    slides.SaveAs(output_file_path, FileFormat=32)
    slides.Close()
# Quick Startup Guide

This repository provides a complete setup to run naive **LeNet Convolutional Neural Network** trained on MNIST dataset on PYNQZ2 hardware using the pre-generated bitstream and hardware description files .

---
### **1. Prerequisites**
Make sure you have the following installed:
- **PYNQ** (v2.7 or later)  
- **Jupyter Notebook** (included with PYNQ image)  
- **Python 3.8+**

If you’re using a PYNQ board (like ZCU104, Z2, etc.), connect it via network and open the Jupyter dashboard in your browser.  
Currently, the bit files support **PYNQ-Z2** only.

---
### **2. Required Files**
The folder `lenet_cnn/software/lenet_software/` contains:
- `lenet_full .bit` — FPGA bitstream  
- `lenet_full .hwh` — Hardware handoff file (describes the design to PYNQ)

Copy these files to your PYNQ board’s home directory before running the notebook.

---

### **3. Run the Jupyter Notebook**
Open the following notebook in Jupyter:

```
lenet_cnn/software/lenet_full.ipynb
```

This notebook:
- Loads the FPGA bitstream and `.hwh` file  
- Initializes the LeNet hardware accelerator  
- Performs inference using the test dataset  
- Displays performance metrics and accuracy  

---

### **4. Expected Output**
You’ll see:
- Bitstream successfully loaded confirmation  
- Accuracy and performance results of the CNN  

---
### **6. File Structure**
```
lenet_cnn/
├── hardware/                # HDL and Vivado design files
├── software/
│   ├── lenet_software/      # Contains lenet.bit and lenet.hwh
│   └── lenet_full.ipynb     # Jupyter notebook for testing and inference
└── README.md
```



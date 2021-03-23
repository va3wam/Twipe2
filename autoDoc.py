###############################################################################
# @file autoDoc.py
# @author the Aging Apprentice
# @brief Twipe2 robot firmware 
# @details Basic operating code for the Twipe2 robot. This file is not used 
# anymore. We now use Github actions to generate documentation at commit time
# which is better than generating it every time we run a build.  
# @copyright Copyright (c) 2021 the Aging Apprentice
# Permission is hereby granted, free of charge, to any person obtaining a copy of 
# this software and associated documentation files (the "Software"), to deal in the 
# Software without restriction, including without limitation the rights to use, copy, 
# modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
# and to permit persons to whom the Software is furnished to do so, subject to the 
# following conditions: The above copyright notice and this permission notice shall 
# be included in all copies or substantial portions of the Software. THE SOFTWARE 
# IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
# BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
# PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
# USE OR OTHER DEALINGS IN THE SOFTWARE.
# 
# YYYY-MM-DD Dev        Description
# ---------- ---------- --------------------------------------------------------
# 2021-03-22 Old Squire Code base created.
################################################################################
import os # Allow us to run command line scripts
os.system("echo Running doxygen to generate updated documentation.") # Send message to terminal.
os.system("rm -R docs/html") # Remove old HTML directory to make sure old files do not hang around.
os.system("rm -R docs/latex") # Remove old LATEX directory to make sure old files do not hang around.
os.system("doxygen") # Run Doxygen which finds Doxy file in same directory and runs it.
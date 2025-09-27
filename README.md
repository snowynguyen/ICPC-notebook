ACM-ICPC Team Reference Notebook 
========================

VinUniversity ICPC Team Reference Notebook. Forked from Stanford ACM-ICPC teams' Github [here](https://github.com/jaehyunp/stanfordacm). The team notebook is compiled from codes written by previous Stanford team members and coaches.

Generating / compiling team notebook
========================
The included Python scripts can generate the notebook in PDF or HTML format. Both scripts read the contents of the notebook from `contents.txt`.

Prerequisites
-----------
A texlive installation is required. The `latexmk` command should be available from the command line. 

Compiling PDF version
-----------
Requires: [Python 2/3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

Script for generating the PDF file is `python generate_pdf.py`.
The LaTeX template that the script uses is `notebook.tex`. It recognizes common file extensions for C/C++/Java/Python/Tex and applies syntax highlighting. In order to change the color scheme or add additional languages, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.

Compiling HTML version
------------
Requires: [Python 2/3](https://www.python.org/), [enscript](https://www.gnu.org/software/enscript/)

Script for generating the HTML file is `generate_html.py`.
Syntax highlighting is handled solely by enscript, and in order to change the color schemes, either the default options of enscript or `generate_html.py` should be edited accordingly.

Contribution to the team notebook
========================

## `contents.txt` 

- The general outline is given in the `contents.txt` file.
- Any line followed by a `#` character is ignored
- Section headings must be in square brackets
- Subsections within a section should follow the format:
- `[filename within /code directory][tab character \t][subsection title]`

Links
=====
* [Original version](https://github.com/jaehyunp/stanfordacm)
* [Stanford Local Programming Contest](http://cs.stanford.edu/group/acm/SLPC/)
* [CS 97SI: Introduction to Programming Contests](http://stanford.edu/class/cs97si/)

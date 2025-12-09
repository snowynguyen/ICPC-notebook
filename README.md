ACM-ICPC Team Reference Notebook 
========================

VinUniversity ICPC Team Reference Notebook. Forked from Stanford ACM-ICPC teams' Github [here](https://github.com/jaehyunp/stanfordacm). The team notebook is compiled from code written by previous Stanford team members and coaches.

Using the notebook
========================
Download the `notebook.pdf` file; everything is in here.

Generating/compiling team notebook
========================
The included Python scripts can generate the notebook in PDF or HTML format. Both scripts read the contents of the notebook from `contents.tsv`.

Prerequisites
-----------
A TexLive installation is required. The `latexmk` command must be available from the command line. This can be done by adding `latexmk` to your shell's PATH variable.  

Python is required and must be available from the command line. 

Compiling PDF version
-----------
Script for generating the PDF file is `python generate_pdf.py`.
The LaTeX template that the script uses is `notebook.tex`. It recognizes common file extensions for C/C++/Java/Python/Tex and applies syntax highlighting. In order to change the color scheme or add additional languages, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.

Compiling HTML version
------------
Requires: [Python 2/3](https://www.python.org/), [enscript](https://www.gnu.org/software/enscript/)

Script for generating the HTML file is `generate_html.py`.
Syntax highlighting is handled solely by enscript, and in order to change the color schemes, either the default options of enscript or `generate_html.py` should be edited accordingly.

Contribution to the team notebook
========================

## `contents.tsv` 

- The general outline is given in the `contents.tsv` file.
- Any line followed by a `#` character is ignored
- Section headings must be in square brackets
- Subsections within a section should follow the format:
- `[filename within /code directory][tab character \t][subsection title]`

Links
=====
* [Original version](https://github.com/jaehyunp/stanfordacm)
* [Stanford Local Programming Contest](http://cs.stanford.edu/group/acm/SLPC/)
* [CS 97SI: Introduction to Programming Contests](http://stanford.edu/class/cs97si/)

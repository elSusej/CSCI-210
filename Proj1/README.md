# CSCI210Project1
A simple bash script that corrects and reorganizes log files. 

This Bash script scans through log files in a specified directory to find and correct invalid calendar dates formatted as MMM/DD/YYYY (ex Feb/30/2021). It adjusts invalid day values to the maximum allowed for the given month and year, accounting for leap years, and then outputs the corrected logs into a structured folder under ./correctedLogs

The general process for doing so is: 

1. Recursively searches files in the input directory for date patterns like Jan/32/2021, Feb/30/2020, etc.

2. Parses and validates each date.

3. Automatically corrects invalid dates (e.g., Feb/30/2021 ➝ Feb/28/2021).

4. Organizes the corrected log files into year-based subdirectories:

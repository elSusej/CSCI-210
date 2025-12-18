#!/bin/bash
#shebang line required for autograder

inputDir="$1"

mkdir -p "correctedLogs"

for FILE in $(grep -lRo "[[:alpha:]]\{3\}/[[:digit:]]\{2\}/[[:digit:]]\{4\}" $inputDir)
do	
	tempFile=$(mktemp)
	while IFS= read -r line;
	do
		if [[ $line =~ ([[:alpha:]]{3})/([0-9]{2})/([0-9]{4}) ]]; then	

			mon="${BASH_REMATCH[1]}"
			day="${BASH_REMATCH[2]}"
			yr="${BASH_REMATCH[3]}"
			
			case $mon in 
				Jan|Mar|May|Jul|Aug|Oct|Dec) DAYS=31;;
				Apr|Jun|Sep|Nov) DAYS=30;;
				Feb)
				if (( (yr % 4 == 0) && (yr % 100 != 0 || yr % 400 == 0) )); then
					DAYS=29
				else
					DAYS=28
				fi;;
			esac

			day=$((10#$day))

			if (( day > DAYS )); then
				day=$DAYS
			fi
			
			UKstd=$(printf "%02d/%s/%s" "$day" "$mon" "$yr")
			
			line="${line//${BASH_REMATCH[0]}/$UKstd}" #string replacement using '//' which is the bash string replacement operator, also BASH_REMATCH[0] should include the entire original pattern that was found isntead of snippets
		
		fi
		echo "$line" >> "$tempFile"
	done < $FILE
	mkdir -p ./correctedLogs/$yr

	mv "$tempFile" "./correctedLogs/$yr/$mon-${yr}_log.txt"
done

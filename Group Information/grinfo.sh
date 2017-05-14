#!/bin/bash
#Abhishek Polavarapu
#Assignment 1
#UIN:01028922



		
optionC()
{
	getent passwd > passwords.txt
	getent group > group.txt
	
	count=$1
	c_count=()
	index=()
	while IFS=":" read -r c1 c2 c3 c4 c5 c6 c7
	do
        if [[ ${c_count[$c4]} -eq "" ]]
        then
        c_count[$c4]=1
        else
                c_count[$c4]=`expr ${c_count[$c4]} + 1`  
                if [[ ${c_count[$c4]} -ge $count ]]; then
                        index+=($c4)
                fi  
    fi  
	
	done < "passwords.txt"

	sorted_unique_ids=$(echo "${index[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' ')

	arr=($sorted_unique_ids)

	line=()
	x=0

printf "Count" > res.txt
printf "\t" >> res.txt
printf "GID" >> res.txt
printf "\t" >> res.txt
printf "Name" >> res.txt
printf "\n" >> res.txt
printf "===" >> res.txt
printf "\t" >> res.txt
printf "=====" >> res.txt
printf "\t" >> res.txt
printf "====" >> res.txt

for i in "${arr[@]}"
do
        word=$(cat group.txt | tr '*' '_' | grep ":$i:[^ ]" |  tr ':' ' '| cut -f 1 -d " ")
        #echo $word
        #id="${arr[$x]}"
        #echo $id 
        printf "\n" >> result.txt
        printf "\n" >> res.txt
        id="${arr[$x]}"
		printf ${c_count[$id]} >> result.txt >> res.txt
        printf "\t" >> result.txt >> res.txt
		printf $id >> result.txt >> res.txt
        printf "\t" >> result.txt >> res.txt
        printf $word >> result.txt >> res.txt
        x=`expr $x + 1`
done
cvalue=$(wc -l <"res.txt")
printf "There are ("
cvalue1=`expr $cvalue - 1`
printf $cvalue1
printf ") groups with atleast ("
printf $count
printf ") members\n"
cat res.txt
rm -r passwords.txt
rm -r group.txt
}


optionU()
{
	getent passwd > passwords.txt
	getent group > group.txt
	uval1=$1
	echo "User Login \""$1"\":" > temp.txt
	
	grep -w "^$uval1" passwords.txt | awk -F: '{printf "User Name : "$5 }' >> temp.txt
	uval2=$(grep -w "^$uval1" passwords.txt   | awk -F: '{print $4}')
	awk -F: '{if ($3=='$uval2' && $4!=null){printf "\nMain Group: "$1} }' group.txt >> temp.txt
	printf "\nAugmented Groups:" >> temp.txt
	grep  "$uval1" group.txt| awk -F: '{printf "\n\t\t"$1}' >> temp.txt
	cat temp.txt
	rm -r temp.txt
	rm -r group.txt
	rm -r passwords.txt
}

optionG()
{
	getent passwd > passwords.txt
	getent group > group.txt
	gval1=$1
	
	GID=$(grep -w "^$gval1" group.txt | awk -F: '{if ($4!=null){printf $3} }')
	grep -w "^$gval1" group.txt | awk -F: '{print $4}' > temp.txt
	tr ',' '\n' < temp.txt > temp1.txt

	cat temp1.txt | sed '/^\s*$/d' > temp2.txt
	count=$(wc -l < "temp2.txt")

	printf "Login" > res.txt
	printf "\t" >> res.txt
	printf "UID" >> res.txt
	printf "\t" >> res.txt
	printf "Name" >> res.txt
	printf "\n" >> res.txt
	printf "=====" >> res.txt
	printf "\t" >> res.txt
	printf "===" >> res.txt
	printf "\t" >> res.txt
	printf "=====" >> res.txt
	
	while read line;
	do
	gval2=(${line})
	gval3=$gval2
	grep -w "^$gval3" passwords.txt | awk -F: '{printf "\n"$1"\t"$3"\t"$5}' >> res.txt
	done < "temp2.txt"
	
	printf "Group  \"" 
	printf $gval1
	printf "\" , " 
	printf " GID  "
	printf $GID
	printf " , " 
	printf " has (" 
	printf $count
	printf ") members : " 
	printf "\n"
	cat res.txt

	rm -r temp.txt
	rm -r temp1.txt
	rm -r temp2.txt
	rm -r res.txt
	rm -r group.txt
	rm -r passwords.txt
}

optionN()
{
	getent passwd > passwords.txt
	printf "Users matching \"" 
	printf $1 
	printf "\"  are  (" 
	grep $1 passwords.txt | awk -F: '{printf "\n"$1":""\t"$5}' >> temp.txt
	count=$(wc -l <"temp.txt")
	printf $count
	printf ") : "
	cat temp.txt 
	rm -r temp.txt
	rm -r passwords.txt
}

optionAC()
{
	getent group > group.txt
	acvalue=$1
	while IFS=":" read -r c1 c2 c3 c4
	do
	array2=(${c1})
	array1=(${c3})
	array=(${c4//,/ })
	printf '%s' "${array2[@]} : " >> temp.txt
	printf '%s' "${array1[@]} : " >> temp.txt
	printf '%s\n' ${#array[@]} >> temp.txt
	set -f
	done < "group.txt"
	
	printf "Count" > temp1.txt
	printf "\t" >> temp1.txt
	printf "GID" >> temp1.txt
	printf "\t" >> temp1.txt
	printf "Name" >> temp1.txt
	printf "\n" >> temp1.txt
	printf "=====" >> temp1.txt
	printf "\t" >> temp1.txt
	printf "===" >> temp1.txt
	printf "\t" >> temp1.txt
	printf "=====" >> temp1.txt

	awk -F: '{if ($3>='$acvalue'){printf "\n"$3"\t"$2"\t"$1}}' temp.txt >> temp2.txt
	acount=$(wc -l <"temp2.txt")
	printf "There are (" 
	printf $acount 
	printf ") augmented groups with atleast  \"" 
	printf $acvalue 
	printf "\" members" 
	printf "\n" 
	cat temp2.txt >> temp1.txt
	cat temp1.txt
	rm -r temp.txt
	rm -r temp2.txt
	rm -r temp1.txt
	rm -r group.txt
}

optionAG()
{
	getent passwd > passwords.txt
	getent group > group.txt
	grep -w ^$1 group.txt > temp.txt
	printf "Augmented Group \"" > temp1.txt
	printf "$1" >> temp1.txt
	agvalue=$( grep -w "^$1" group.txt | awk -F: '{print $3 } ')
	agcount=$( grep -w ^$1 group.txt | awk -F:  '{print $4 } ')
	printf "\", " >> temp1.txt
	printf "GID " >> temp1.txt
	printf  "$agvalue" >> temp1.txt
	printf ", " >> temp1.txt
	printf "has (" >> temp1.txt
	printf $agcount | tr ',' ' ' | wc -w >> temp1.txt
	printf " )members :" >> temp1.txt
	printf "\n" >> temp1.txt
	printf "Login\t" >> temp1.txt
	printf "MainGroup\t" >>temp1.txt
	printf "Name\t\n" >>temp1.txt
	printf "=====\t" >>temp1.txt
	printf "=========\t" >>temp1.txt
	printf "====\t\n" >>temp1.txt
	
	while IFS=":" read -r c1 c2 c3 c4
	do
	set -f
	array=(${c4//,/ })
	for i in "${!array[@]}"
	do
	printf "${array[i]}" >> temp1.txt
	printf "\t" >> temp1.txt 
	value=$( grep -w "^${array[i]}" passwords.txt | awk -F: '{print $4 } ')
	getent group | awk -F: '{if ($3=='$value' && $4!=null){printf $1} }' >> temp1.txt
	printf "\t\t" >>temp1.txt
	grep -w "^${array[i]}" passwords.txt | awk -F: '{printf $5 } ' >>temp1.txt
	printf "\n" >> temp1.txt
	done
	cat temp1.txt
	done < "temp.txt"
	
	rm -r temp.txt
	rm -r temp1.txt
	rm -r group.txt
	rm -r passwords.txt
}

noOption()
{
	printf "Usage: grinfo [-c <count> | -g <group> | -u <user> | -n <name> | -ac <count> | -ag <group>]\n"
	printf "Examples:\n"
	printf "grinfo               // Help\n"
	printf "grinfo -c 10         // List groups of at least 10.\n"
	printf "grinfo -g staff      // Details of group staff\n"
	printf "grinfo -u wahab      // Details of user wahab\n"
	printf "grinfo -n abd        // List users that have abd in thier login or name.\n"
	printf "grinfo -ac 10        // List augmented groups of at least 10.\n"
	printf "grinfo -ag staff     // Details of augmented group staff\n"
	}


		if [ $# -eq 0 ]
		then
		noOption
		exit

	#option C
		elif  [ $1 = "-c" ]; then
    			echo "Retrieving data:"
			optionC $2
			exit
	#option G
		elif  [ $1 = "-g" ]; then
    		echo "Retrieving data:"
			optionG $2
			
			
	#option u
		elif  [ $1 = "-u" ]; then
    		echo "Retrieving data:"
			optionU $2
			exit
		
	#option n
		elif  [ $1 = "-n" ]; then
    		echo "Retrieving data:"
			optionN $2
			exit
		
	#option ac
		elif  [ $1 = "-ac" ]; then
    		echo "Retrieving data:"
			optionAC $2
			exit
		
	#option ag
		elif  [ $1 = "-ag" ]; then
    		echo "Retrieving data:"
			optionAG $2
			exit	
		else
			echo "Enter the correct option"
		fi



psql=(psql -v ON_ERROR_STOP=1 --username "$POSTGRES_USER" --no-password --dbname "$POSTGRES_DB")

for f in /docker-entrypoint-initdb.d/*/*; do 
 	case "$f" in 
 		*.sh) 
 			if [ -x "$f" ]; then 
 				echo "$0: running $f" 
 				"$f"
 			else 
 				echo "$0: sourcing $f" 
 				. "$f"
 			fi 
 			;; 
 		*.sql)    echo "$0: running $f"; "${psql[@]}" -f "$f"; echo ;; 
 		*.sql.gz) echo "$0: running $f"; gunzip -c "$f" | "${psql[@]}"; echo ;; 
 		*)        echo "$0: ignoring $f" ;; 
 	esac 
 	echo 
 done 
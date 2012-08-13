cp lib/libSapling.so /usr/local/lib/

TARGET=/usr/local/include/sapling
if [[ ! -e $TARGET/Components ]]; then
  mkdir -p $TARGET/Components
  mkdir -p $TARGET/Systems
  mkdir -p $TARGET/Wrappers
fi
cp *.h $TARGET
cp Components/*.h $TARGET/Components
cp Systems/*.h $TARGET/Systems
cp Wrappers/*.h $TARGET/Wrappers

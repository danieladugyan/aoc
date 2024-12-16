for file in *.dzn; do
    /mnt/c/Program\ Files/MiniZinc/minizinc.exe model.mzn $file --solver cpsatlp >> output.txt
done
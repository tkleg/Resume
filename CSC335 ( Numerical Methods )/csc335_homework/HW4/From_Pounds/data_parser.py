in_file_name = "Gauss_Laguerre_*_Point_Data.txt"
for n in [3, 7, 15]:
    file = in_file_name.replace("*", str(n))
    with open(file, 'r') as f:
        lines = f.readlines()
        x_lines = [line.strip() for line in lines if line.strip().startswith("X")]
        w_lines = [line.strip() for line in lines if line.strip().startswith("W")]
        values = []
        with open(f"GLa_{n}_Points.txt", 'w') as out:
            for x_line in x_lines:
                x_num = int( x_line[2:4] )
                for w_line in w_lines:
                    w_num = int( w_line[2:4] )
                    if x_num == w_num:
                        x_val = float( x_line[8:-1] )
                        w_val = float( w_line[8:-1] )
                        values.append( (x_val, w_val) )
                        out.write(f"{x_val} {w_val}\n")
                        break


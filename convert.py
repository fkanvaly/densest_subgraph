
        #      name         separator
dataset = {"com-youtube":   "\t", 
           "com-dblp":      "\t",
           "cit-HepPh":     "\t",
           "email-EuAll":   "\t",
           "email-Eu-core": " "
            }

for name, sep in dataset.items():
    print(name)
    input_f = f"../input/{name}.txt"
    output_f = f"../output/{name}.txt"
    out= open(output_f,"w")
    with open(input_f) as f:
        for i, line in enumerate(f.readlines()):
            if line[0] == "#": continue
            src, dst = line.split(sep)[:2]
            out.write(f"{src} {dst}")
    out.close()
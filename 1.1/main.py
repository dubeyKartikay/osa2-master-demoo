import plotext as plt
import csv
data =[]
with open("./results", 'r') as file:
  csvreader = csv.reader(file)
  for row in csvreader:
    if(row == []):
      continue
    data.append(row);
data = data[1:]
print(*data,sep="\n");
rr_data = data[:6]
fifo_data =data[6:]


rr_prs = list(map(lambda x : int(x[1]),rr_data))
rr_time_rr = list(map(lambda x :   float(x[3])*100,rr_data))
rr_time_fifo = list(map(lambda x : float(x[2])*100,rr_data))
rr_time_other = list(map(lambda x :float(x[4])*100,rr_data))


fifo_prs = list(map(lambda x :          int(x[0]),fifo_data))
fifo_time_rr = list(map(lambda x :    float(x[3])*100,   fifo_data))
fifo_time_fifo = list(map(lambda x :  float(x[2])*100, fifo_data))
fifo_time_other = list(map(lambda x : float(x[4])*100,fifo_data))

print(*rr_time_rr,sep="\n")
print("#################W")
print(*fifo_time_rr,sep="\n")

pizzas = [1, 5, 10, 20, 60, 99]
male_percentages = [14, 36, 11, 8, 7, 4]
female_percentages = [12, 20, 35, 15, 2, 1]

plt.multiple_bar(fifo_prs, [fifo_time_other,fifo_time_rr,fifo_time_fifo], label = ["OTHER", "RR","FIFO"])
plt.title("FIFO priority was varied keeping RRs and Others priority the same")

plt.show()
plt.clear_figure()
plt.multiple_bar(rr_prs, [rr_time_other,rr_time_fifo, rr_time_rr], label = ["OTHER", "FIFO","RR"])
plt.title("RR priority was varied keeping RRs and Others priority the same")

plt.show()
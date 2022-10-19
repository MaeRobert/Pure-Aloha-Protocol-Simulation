import matplotlib.pyplot as plt
  
nums = []
nb_of_nums = []
  
f = open('res.txt','r')
for row in f:
    row = row.split(' ')
    nums.append(row[0])
    nb_of_nums.append(float(row[1]))
  
plt.plot(nums, nb_of_nums, color = 'g', label = 'File Data')
  
plt.xlabel('Lambda', fontsize = 12)
plt.ylabel('Number of successful transmissions', fontsize = 12)
  
plt.title('Simulation of aloha protocol', fontsize = 20)
plt.legend()
plt.show()


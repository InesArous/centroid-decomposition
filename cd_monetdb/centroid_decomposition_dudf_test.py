from collections import OrderedDict
from monetdb_centroid_decomposition import process_data

data = OrderedDict( {
	'x1' : [1,2,3],
	'x2' : [3,4,5]
})

print(process_data(data))

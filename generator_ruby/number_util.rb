class NumberUtil

def unsigned_binary_to_float binary_string
 x = 0
 p = 1.0
 k = 1
 binary_string.chars.to_a.each do |c|
   if c!='.'   
     x *= 2
	 x += c.to_i
	 p *=k
   else
     k = 2   
   end 
   
 end
 x /= p
 return x
end

def signed_binary_to_float binary_string
 x = 0
 p = 1.0
 k = 1
 q = 2.0
 binary_string.chars.to_a[1..-1].each do |c|
   if c!='.'   
     x *= 2
	 x += c.to_i
	 p *=k
	 q *= 2
   else
     k = 2   
   end 
   
 end
 x -= q
 x /= p
 return x
end

end

n = NumberUtil.new
puts n.unsigned_binary_to_float("11.1")
puts n.unsigned_binary_to_float("10.01")
puts n.unsigned_binary_to_float("1001.101")
puts n.unsigned_binary_to_float("10001.01001")
puts n.unsigned_binary_to_float("110.011")
puts n.unsigned_binary_to_float("10.1")
puts "---------------"
puts n.signed_binary_to_float("11.1")
puts n.signed_binary_to_float("10.01")
puts n.signed_binary_to_float("1001.101")
puts n.signed_binary_to_float("10001.01001")
puts n.signed_binary_to_float("110.011")
puts n.signed_binary_to_float("10.1")
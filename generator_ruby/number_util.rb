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
 x -= q*binary_string[0].to_i
 x /= p
 return x
end

def float_to_unsigned_8_8 x
   x *= 2**8
   x = x.floor
   p = 0
   s = ""
   while (x>0)
     s += (x%2).to_s
	 x /= 2
	 p += 1
	 if (p==8) 
	  s +="."
	 end
   end
   (p..15).each do |k|
     s += "0"
   end
   s.reverse!
   return s
end

def float_to_signed_8_8 x
 if x>=0 
  return float_to_unsigned_8_8 x
 end
 x +=2**8
 s = float_to_unsigned_8_8 x
 y = unsigned_binary_to_float s
 y += 2**(-8)
 s = float_to_unsigned_8_8 y
 s[0] = '1'
 return s
end


end


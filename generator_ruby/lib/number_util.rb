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
 q = 1.0
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
 x -= (q*binary_string.chars.to_a[0].to_i)
 x /= p
 return x
end

def float_to_unsigned_8_8 x
 float_to_unsigned(x,8,8)
end

def float_to_signed_8_8 x
 if x>=0 
  return float_to_unsigned_8_8 x
 end
 x +=2**8
 s = float_to_unsigned_8_8 x 
 s[0] = '1'
 return s
end

def float_to_unsigned_16_16 x
 float_to_unsigned(x,16,16)
end


def float_to_unsigned(x,int_size,fract_size)
  x *= 2**(fract_size)
  x = x.floor
  p = 0
  s = ""
  t = fract_size+int_size - 1
  while ((x>0) and (p<=t))
    s += (x%2).to_s
    x /= 2
    p += 1
    if (p==fract_size) 
     s +="."
    end
  end
    
  if p<fract_size
    (p..fract_size-1).each do |k|
        s+="0"
     end
  s+="."
  p=fract_size
  end
  
  (p..t).each do |k|
      s += "0"
  end
    
  s.reverse!
  return s   
end

def float_to_signed(x,int_size,fract_size)
  if x>=0 
   return float_to_unsigned(x,int_size,fract_size)
  end
  
  x +=2**int_size
  s = float_to_unsigned(x,int_size,fract_size) 
  s[0] = '1'
  return s
end
  
def float_to_signed_16_16 x
 if x>=0 
  return float_to_unsigned_16_16 x
 end
 
 
 x +=2**16
 s = float_to_unsigned_16_16 x 
 s[0] = '1'
 return s
end

def cast_8_8_to_16_16 x
  return "0000#{x}0000"
end

def cast_16_16_to_8_8 x
  return x[8..-9]
end

def multiply(t1,t2)
  t1_i = t1.floor; t1_f = t1 - t1.floor;
  t2_i = t2.floor; t2_f = t2 - t2.floor;
  rez_i = t1_i * t2_i + (t1_i * t2_f + t1_f * t2_i + t1_f * t2_f).floor 
  rez_f = t1_i * t2_f + t1_f * t2_i + t1_f * t2_f - (t1_i * t2_f + t1_f * t2_i + t1_f * t2_f).floor
  return [rez_i,rez_f]
end
  
end




require "../lib/generator.rb"

class GeneratorAdd < Generator
 
 attr_accessor :test_title
 
 def initialize options
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{options["test_file_name"]}"
  @no_of_operands = 2
  @test_title = options["title"]
  @type_of_operands = "FIXED POINT BINARY"
  @type_of_result = "FIXED POINT BINARY"
  @saturated = options["saturated"]
  @operand_type = options["type"]
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   
   case @operand_type
   when "8_8":
     range = 2**8
     min = - 2**7
     max = 2**7 - 2**(-8)
     t1 = @gen.generate_fixed_point(8,8)
     t2 = @gen.generate_fixed_point(8,8)  
   when "16_16":
     range = 2**16
     min = - 2**15
     max = 2**15 - 2**(-16)
     t1 = @gen.generate_fixed_point(16,16)
     t2 = @gen.generate_fixed_point(16,16)
   when "8_24":
     range = 2**8
     min = - 2**7
     max = 2**7 - 2**(-24)
     t1 = @gen.generate_fixed_point(8,24)
     t2 = @gen.generate_fixed_point(8,24)
   when "24_8":
     range = 2**24
     min = - 2**23
     max = 2**23 - 2**(-8)
     t1 = @gen.generate_fixed_point(24,8)
     t2 = @gen.generate_fixed_point(24,8)
   else 
     
   end    
     
   
   test["first_operand"] = t1
   test["second_operand"] = t2
     
   r = (@util.signed_binary_to_float(t1)+@util.signed_binary_to_float(t2))  
  
   if @saturated
    
     if r >= max
       r = max
     end
     if r < min
       r = min
     end

   else 
     r = r % range
   end
   
   rez = ""
   case @operand_type
   when "8_8":
     rez = @util.float_to_signed_8_8(r)
   when "16_16":
     rez = @util.float_to_signed_16_16(r)
   when "8_24":
     rez = @util.float_to_signed(r,8,24)
   when "24_8":
     rez = @util.float_to_signed(r,24,8)
   end
   
   test["result"] = rez 
   
   return test
 end
 
 def make_tests
   write_metadata()
   (0..100).each do |k|
      test_hash = generate_test(k)
      write_test(test_hash)
   end
  end
 
end


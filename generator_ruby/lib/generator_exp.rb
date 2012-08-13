require "./generator.rb"


class GeneratorExp < Generator
 
 attr_accessor :test_title
 
 def initialize options
   init_generator() 
   @test_file_name = "#{@path_to_tests_folder}/#{options["test_file_name"]}"
   @no_of_operands = 1
   @test_title = options["title"];
   @type_of_result = "FIXED POINT BINARY"
   @type_of_operands = "FIXED POINT BINARY"
   @operand_type = options["type"]
   @saturated = options["saturated"]
  end
 
 def generate_test test_no
     test = {}
     test["test_no"] = test_no
     case @operand_type
     when "8_8":
       k = @gen.generate_fixed_point(8,8)
       min = - 2**7
       max = 2**7 - 2**(-8)
       #k = k[0...1]*5+k
     when "16_16":
       k = @gen.generate_fixed_point(16,16)
       min = - 2**15
       max = 2**15 - 2**(-16)
       #k = k[0...1]*12+k   
     when "8_24":
       k = @gen.generate_fixed_point(8,24)
       min = - 2**7
       max = 2**7 - 2**(-24)
       #k = k[0...1]*5+k
     when "24_8":
       k = @gen.generate_fixed_point(24,8)
       min = - 2**23
       max = 2**23 - 2**(-8)
       #k = k[0...1]*19+k        
     end
     
     test["first_operand"] = k
     n = @util.signed_binary_to_float(k)
     
     rez = Math.exp(n)
     if rez > max and @saturated
       rez = max
     end

     case @operand_type
     when "8_8":
       rez = @util.float_to_signed(rez,8,8)
     when "16_16":
       rez = @util.float_to_signed(rez,16,16)
     when "8_24":
       rez = @util.float_to_signed(rez,8,24);
     when "24_8":
       rez = @util.float_to_signed(rez,24,8);
     end

     if @saturated
       if rez<=min 
         rez = min
       end
       
       if rez>=max
         rez = max
       end
     end
     
     test["result"] = rez
     return test
   end
 
 def make_tests
  write_metadata()
  (0..1000).each do |k|
     test_hash = generate_test(k)
     write_test(test_hash)
  end
 end

end

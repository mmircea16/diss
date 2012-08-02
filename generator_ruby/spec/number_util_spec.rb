require "../lib/number_util.rb"
require "rspec"
describe NumberUtil do
  
  before :all do
    @util = NumberUtil.new
  end
  
  it "should return correct value for 0's representation in unsigned binary" do
    @util.unsigned_binary_to_float("0.0").should eq(0)
    @util.unsigned_binary_to_float("0.0000").should eq(0)
    @util.unsigned_binary_to_float("0.00").should eq(0)
  end
  
  it "should return correct value for sub-unitar values in unsigned binary" do
    @util.unsigned_binary_to_float("0.1").should eq(0.5)
    @util.unsigned_binary_to_float("0.0010").should eq(0.125)
    @util.unsigned_binary_to_float("0.101").should eq(0.625)
    @util.unsigned_binary_to_float("00.01101").should eq(0.40625)
    @util.unsigned_binary_to_float("0.0010101100").should eq(0.16796875)
  end
  
  it "should retun correct values for integer representation in unsigned binary" do
    @util.unsigned_binary_to_float("1.0").should eq(1)
    @util.unsigned_binary_to_float("11.000").should eq(3)
    @util.unsigned_binary_to_float("1101.00").should eq(13)
    @util.unsigned_binary_to_float("101101.0").should eq(45)
    @util.unsigned_binary_to_float("10101101.000000000").should eq(173)
  end
  
  it "should return correct values for real numbers with fractional and integer part diff from 0" do
    @util.unsigned_binary_to_float("1.01").should eq(1.25)
    @util.unsigned_binary_to_float("101.011").should eq(5.375)
    @util.unsigned_binary_to_float("1001.1010").should eq(9.625)
    @util.unsigned_binary_to_float("101101.01101").should eq(45.40625)
    @util.unsigned_binary_to_float("10101101.0010101100").should eq(173.16796875)
  end
  
  it "should return correct values for 0's in signed binary" do
    @util.signed_binary_to_float("0.0").should eq(0)
    @util.signed_binary_to_float("0.0000").should eq(0)
    @util.signed_binary_to_float("0.00").should eq(0)
  end
  
  it "should return correct value for positive sub-unitar values in signed binary" do
    @util.signed_binary_to_float("0.1").should eq(0.5)
    @util.signed_binary_to_float("0.0010").should eq(0.125)
    @util.signed_binary_to_float("0.101").should eq(0.625)
    @util.signed_binary_to_float("00.01101").should eq(0.40625)
    @util.signed_binary_to_float("0.0010101100").should eq(0.16796875)
  end
  
  it "should retun correct values for positive integer representation in signed binary" do
     @util.signed_binary_to_float("01.0").should eq(1)
     @util.signed_binary_to_float("011.000").should eq(3)
     @util.signed_binary_to_float("01101.00").should eq(13)
     @util.signed_binary_to_float("0101101.0").should eq(45)
     @util.signed_binary_to_float("010101101.000000000").should eq(173)
   end
   
  it "should return correct values for positive real numbers with fractional and integer part diff from 0" do
    @util.signed_binary_to_float("01.01").should eq(1.25)
    @util.signed_binary_to_float("0101.011").should eq(5.375)
    @util.signed_binary_to_float("01001.1010").should eq(9.625)
    @util.signed_binary_to_float("0101101.01101").should eq(45.40625)
    @util.signed_binary_to_float("010101101.0010101100").should eq(173.16796875)
  end
  
  it "should return correct value for negative sub-unitar values in signed binary" do
      @util.signed_binary_to_float("11.1").should eq(-0.5)
      @util.signed_binary_to_float("1.0010").should eq(-0.875)
      @util.signed_binary_to_float("1.101").should eq(-0.375)
      @util.signed_binary_to_float("111.01101").should eq(-0.59375)
      @util.signed_binary_to_float("1.0010101100").should eq(-0.83203125)
  end
  

  it "should retun correct values for negative integer representation in signed binary" do
     @util.signed_binary_to_float("11.0").should eq(-1)
     @util.signed_binary_to_float("1001.000").should eq(-7)
     @util.signed_binary_to_float("11101.00").should eq(-3)
     @util.signed_binary_to_float("1100111.0").should eq(-25)
     @util.signed_binary_to_float("110101101.000000000").should eq(-83)
   end

  it "should return correct values for negative real numbers with fractional and integer part diff from 0" do
    @util.signed_binary_to_float("101.01").should eq(-2.75)
    @util.signed_binary_to_float("10101.011").should eq(-10.625)
    @util.signed_binary_to_float("11001.1010").should eq(-6.375)
    @util.signed_binary_to_float("10101101.01101").should eq(-82.59375)
    @util.signed_binary_to_float("1000101101.0010101100").should eq(-466.83203125)
  end
  
  it "should return correct string values for 0 transformation into unsigned binary" do
    @util.float_to_unsigned_8_8(0).should eq("00000000.00000000")
  end

  it "should return correct string values for subunitar value transformation into unsigned binary" do
    @util.float_to_unsigned_8_8(0.5).should eq("00000000.10000000")
    @util.float_to_unsigned_8_8(0.125).should eq("00000000.00100000")
    @util.float_to_unsigned_8_8(0.2).should eq("00000000.00110011")
    @util.float_to_unsigned_8_8(0.3).should eq("00000000.01001100")
    @util.float_to_unsigned_8_8(0.37841).should eq("00000000.01100000")
    @util.float_to_unsigned_8_8(0.69323).should eq("00000000.10110001")
  end
  
  it "should return correct string values for integer values transformation into unsigned binary" do
    @util.float_to_unsigned_8_8(1.0).should eq("00000001.00000000")
    @util.float_to_unsigned_8_8(12.0).should eq("00001100.00000000")
    @util.float_to_unsigned_8_8(23.0).should eq("00010111.00000000")
    @util.float_to_unsigned_8_8(123.0).should eq("01111011.00000000")
  end
  
  it "should return correct string values for real values transformation into unsigned binary" do
    @util.float_to_unsigned_8_8(1.5).should eq("00000001.10000000")
    @util.float_to_unsigned_8_8(13.125).should eq("00001101.00100000")
    @util.float_to_unsigned_8_8(27.167).should eq("00011011.00101010")
    @util.float_to_unsigned_8_8(76.9158).should eq("01001100.11101010")
  end
  
  it "should return correct string values for 0 transformation into signed binary" do
    @util.float_to_signed_8_8(0).should eq("00000000.00000000")
  end
  
  it "should return correct values for positive numbers into signed binary" do
    @util.float_to_signed_8_8(0.5).should eq("00000000.10000000")
    @util.float_to_signed_8_8(0.125).should eq("00000000.00100000")
    @util.float_to_signed_8_8(23.0).should eq("00010111.00000000")
    @util.float_to_signed_8_8(123.0).should eq("01111011.00000000")
    @util.float_to_signed_8_8(27.167).should eq("00011011.00101010")
    @util.float_to_signed_8_8(76.9158).should eq("01001100.11101010")
  end
  
  it "should return correct values for negative sub-unitar numbers into signed binary" do
    @util.float_to_signed_8_8(-0.5).should eq("11111111.10000000")
    @util.float_to_signed_8_8(-0.125).should eq("11111111.11100000")
    @util.float_to_signed_8_8(-0.713).should eq("11111111.01001001")
  end
  
  it "should return correct values for negative integers into signed binary" do
    @util.float_to_signed_8_8(-1).should eq("11111111.00000000")
    @util.float_to_signed_8_8(-9).should eq("11110111.00000000")
    @util.float_to_signed_8_8(-71.0).should eq("10111001.00000000")
  end
  
  it "should return correct values for real numbers into signed binary" do
    @util.float_to_signed_8_8(-13.587).should eq("11110010.01101001")
    @util.float_to_signed_8_8(-6.375).should eq("11111001.10100000")
    @util.float_to_signed_8_8(-82.59375).should eq("10101101.01101000") 
    @util.float_to_signed_8_8(-101.0281).should eq("10011010.11111000")
  end
  
  it "should return correct values for real numbers into signed binary 16.16" do
     @util.float_to_signed_16_16(-13.587).should eq("1111111111110010.0110100110111010")  
     @util.float_to_signed_16_16(-6.375).should eq("1111111111111001.1010000000000000")
     @util.float_to_signed_16_16(-82.59375).should eq("1111111110101101.0110100000000000") 
     @util.float_to_signed_16_16(101.0281).should eq("0000000001100101.0000011100110001")
   end
   
   it "should return correct values for complement of 2" do
     @util.complement_of_2("0100010010.0001").should eq("1011101101.1111")
     @util.complement_of_2("010001110.100").should eq("101110001.100")
     @util.complement_of_2("1011110.0000").should eq("0100010.0000")
       
   end
  
end
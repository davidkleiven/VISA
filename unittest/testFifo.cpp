#include "fifoBuffer.hpp"
#include <gtest/gtest.h>

TEST( FIFOTest, 1 )
{
  visa::FIFOBuffer<double> buffer(4);
  buffer.push_back(1.0);
  buffer.push_back(2.0);
  buffer.push_back(3.0);
  buffer.push_back(4.0);

  EXPECT_NEAR( 1.0, buffer.get(0), 1E-5 );
  EXPECT_NEAR( 2.0, buffer.get(1), 1E-5 );
  EXPECT_NEAR( 3.0, buffer.get(2), 1E-5 );
  EXPECT_NEAR( 4.0, buffer.get(3), 1E-5 );

  buffer.push_back(5.0);

  EXPECT_NEAR( 2.0, buffer.get(0), 1E-5 );
  EXPECT_NEAR( 3.0, buffer.get(1), 1E-5 );
  EXPECT_NEAR( 4.0, buffer.get(2), 1E-5 );
  EXPECT_NEAR( 5.0, buffer.get(3), 1E-5 );

  buffer.push_back(6.0);

  EXPECT_NEAR( 3.0, buffer.get(0), 1E-5 );
  EXPECT_NEAR( 4.0, buffer.get(1), 1E-5 );
  EXPECT_NEAR( 5.0, buffer.get(2), 1E-5 );
  EXPECT_NEAR( 6.0, buffer.get(3), 1E-5 );
}

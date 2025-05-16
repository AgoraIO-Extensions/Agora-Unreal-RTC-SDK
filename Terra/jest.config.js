module.exports = {
  projects: [
    {
      displayName: 'test',
      coverageDirectory: 'test',
      preset: 'ts-jest',
      testEnvironment: 'node',
      testRegex: './*/__tests__/.*\\.(test|spec)\\.[jt]sx?$',
    },
    {
      displayName: 'integration',
      coverageDirectory: 'integration',
      preset: 'ts-jest',
      testEnvironment: 'node',
      testRegex: './*/__integration_test__/.*\\.integration\\.test\\.[jt]sx?$',
    },
    {
      displayName: 'cxx-parser',
      coverageDirectory: 'cxx-parser',
      preset: 'ts-jest',
      testEnvironment: 'node',
      testRegex: 'cxx-parser/__tests__/.*\\.(test|spec)\\.[jt]sx?$',
    },
    {
      displayName: 'integration:cxx-parser',
      coverageDirectory: 'integration:cxx-parser',
      preset: 'ts-jest',
      testEnvironment: 'node',
      testRegex:
        'cxx-parser/__integration_test__/.*\\.integration\\.test\\.[jt]sx?$',
    },
    {
      displayName: 'terra',
      coverageDirectory: 'terra',
      preset: 'ts-jest',
      testEnvironment: 'node',
      testRegex: 'terra/__tests__/.*\\.(test|spec)\\.[jt]sx?$',
    },
    {
      displayName: 'terra-core',
      coverageDirectory: 'terra-core',
      preset: 'ts-jest',
      testEnvironment: 'node',
      testRegex: 'terra-core/__tests__/.*\\.(test|spec)\\.[jt]sx?$',
    },
  ],
};
